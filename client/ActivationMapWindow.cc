#include <stddef.h>
#ifdef _WIN32
#include <windows.h>
#pragma warning(disable:4505)
#undef TRACE
#else
#include <unistd.h>
#endif
#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

#include <float.h>
#include <limits.h>
#include <math.h>
#include <string>
#include "colormaps.h"
#include "dialogs.h"
#include "map3dmath.h"
//#include "GeomWindow.h"
#include "Contour_Info.h"
#include "Map3d_Geom.h"
#include "Surf_Data.h"
#include "WindowManager.h"
#include "LegendWindow.h"
#include "PickWindow.h"
#include "MainWindow.h"
#include "ProcessCommandLineOptions.h"
#include "Transforms.h"
#include "BallMath.h"
#include "glprintf.h"
#include "eventdata.h"
#include "landmarks.h"
#include "lock.h"
#include "pickinfo.h"
#include "readfiles.h"
#include "reportstate.h"
#include "GeomWindowMenu.h"
#include "FileDialog.h"
#include "GetMatrixSlice.h"
#include "texture.h"

#include <algorithm>

#include <QFile>
#include <QDebug>
#include <QCloseEvent>
#include <QLayout>

#include "ActivationMapWindow.h"

#include "GenericWindow.h"
#include "MeshList.h"
#include "GeomWindowMenu.h"

#include <QApplication>
#include <QDesktopWidget>

#include "dialogs.h"
#include <QList>

extern Map3d_Info map3d_info;
extern MainWindow *masterWindow;

static const int min_width = 200;
static const int min_height = 200;
static const int default_width = 380;
static const int default_height = 380;

GLuint selectbufferActivate[2048];


ActivationMapWindow::ActivationMapWindow(QWidget *parent) : Map3dGLWidget(parent, ACTIVATIONWINDOW, "Activation Display",min_width, min_height)
{
    // things that need to be set before Init happens
    xmin = ymin = zmin = FLT_MAX;
    xmax = ymax = zmax = -FLT_MAX;
    clip = new Clip_Planes; //init the Clipping planes

#ifdef ROTATING_LIGHT
    Ball_Init(&light_pos, 1);
    Ball_Place(&light_pos, qOne, .8);
#endif

    dominantsurf = -1;
    secondarysurf = -1;
    vfov = 29.0f;
    fog1 = 1.8f;
    fog2 = 2.2f;
    bgcolor[0] = bgcolor[1] = bgcolor[2] = 0;
    fgcolor[0] = fgcolor[1] = fgcolor[2] = 1;
    showinfotext = 1;
    all_axes = 1;
    rgb_axes = true;
    modifiers = 0;
    l2norm = 0;
}

ActivationMapWindow* ActivationMapWindow::ActivationMapWindowCreate(int _width, int _height, int _x, int _y)
{
    ActivationMapWindow* win = new ActivationMapWindow(masterWindow ? masterWindow->childrenFrame : NULL);
    win->positionWindow(_width, _height, _x, _y, default_width, default_height);
    win->show();
    return win;
}

void ActivationMapWindow::initializeGL()
{
    Map3dGLWidget::initializeGL();
    // FIX GeomBuildMenus(this);

    this->light_position[0] = 0.f;
    this->light_position[1] = fabs(2 * this->l2norm);
    this->light_position[2] = 0.f;
    this->light_position[3] = 1.f;

    lighting_direction = graphics_light_above; // see Menu for which is which

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glShadeModel(GL_FLAT);

    glFogfv(GL_FOG_COLOR, this->bgcolor);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glEnable(GL_COLOR_MATERIAL);
    glDepthFunc(GL_LEQUAL);
    glPolygonOffset(1, 2);
    glDisable(GL_POLYGON_OFFSET_FILL);
    glDisable(GL_POLYGON_OFFSET_LINE);
    glDisable(GL_POLYGON_OFFSET_POINT);
    glSelectBuffer(2048, selectbufferActivate);
    glLineStipple(1, 57795);
}


void ActivationMapWindow::paintGL()
{
    int loop = 0;
    int length = meshes.size();

    Mesh_Info *curmesh = 0;

    /* clear the screen */
    glClearColor(bgcolor[0], bgcolor[1], bgcolor[2], 1);
    glFogfv(GL_FOG_COLOR, bgcolor);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // if it exists, draw a background image
    if (map3d_info.bg_texture)
        DrawBGImage();


    glFogf(GL_FOG_START, l2norm * fog1);
    glFogf(GL_FOG_END, l2norm * fog2);

    if (length > 1 && !map3d_info.lockgeneral) {
        loop = dominantsurf;
        length = loop + 1;
    }

#ifdef ROTATING_LIGHT
    // draw rotated light
    HMatrix mNow;
    Ball_Value(&light_pos, mNow);
    glMultMatrixf((float *)mNow);
#endif
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    if (clip->front_enabled)
        glEnable(GL_CLIP_PLANE0);
    else
        glDisable(GL_CLIP_PLANE0);

    if (clip->back_enabled)
        glEnable(GL_CLIP_PLANE1);
    else
        glDisable(GL_CLIP_PLANE1);

    /* render each mesh in this window : OPAQUE PASS */
    for (; loop < length; loop++) {
        /* setup a bunch of variables for quick acces */
        curmesh = (meshes[loop]);

        if (curmesh->lighting)
            glEnable(GL_LIGHTING);
        if (curmesh->fogging)
            glEnable(GL_FOG);

        /* compute the mesh position (rotations, translations, etc.) */
        Transform(curmesh, 0, true);

        glEnable(GL_POLYGON_OFFSET_FILL);
        DrawSurf(curmesh);
        glDisable(GL_POLYGON_OFFSET_FILL);

//        /* draw the color mapped surface */
//        if (curmesh->shadingmodel != SHADE_NONE && curmesh->geom->points[curmesh->geom->geom_index] && !curmesh->shadefids &&
//                curmesh->data && curmesh->drawmesh != RENDER_MESH_ELTS && curmesh->drawmesh != RENDER_MESH_ELTS_CONN) {
//            glEnable(GL_POLYGON_OFFSET_FILL);

//            DrawSurf(curmesh);
//            glDisable(GL_POLYGON_OFFSET_FILL);
//        }

    }


#if SHOW_OPENGL_ERRORS
    GLenum e = glGetError();
    if (e)
        printf("GeomWindow Repaint OpenGL Error: %s\n", gluErrorString(e));
#endif
}

void ActivationMapWindow::DrawSurf(Mesh_Info * curmesh)
{

    int length = 0;
    int index;
    int loop2, loop3;
    float a = 1, b = 0;
    float mean = 0;
    float **modelpts = 0;
    float **ptnormals = 0;
    float **fcnormals = 0;
    Map3d_Geom *curgeom = 0;
    Surf_Data *cursurf = 0;

    int  maxactivation, minactivation;

    curgeom = curmesh->geom;
    cursurf = curmesh->data;

    modelpts = curgeom->points[curgeom->geom_index];
    ptnormals = curgeom->ptnormals;
    fcnormals = curgeom->fcnormals;

    maxactivation = *std::max_element(cursurf->activationvals,cursurf->activationvals+curgeom->numpts);
    minactivation = *std::min_element(cursurf->activationvals,cursurf->activationvals+curgeom->numpts);

    unsigned char color[3];


    bool use_textures = false;
    // gouraud shading
    if (curmesh->shadingmodel == SHADE_GOURAUD) {

        glShadeModel(GL_SMOOTH);
        use_textures = curmesh->gouraudstyle == SHADE_TEXTURED &&
                (curmesh->cmap->type == RAINBOW_CMAP || curmesh->cmap->type == JET_CMAP);

        if (use_textures) {
            glColor4f(1,1,1,0.4);
            glEnable(GL_TEXTURE_1D);
            if (curmesh->cmap->type == RAINBOW_CMAP)
                UseTexture(map3d_info.rainbow_texture);
            else
                UseTexture(map3d_info.jet_texture);
        }
    }
    else if (curmesh->shadingmodel == SHADE_FLAT){
        glShadeModel(GL_FLAT);
        glColor4ub(color[0],color[1],color[2],color[3]);
    }

    if (curgeom->elementsize == 3 && curmesh->shadingmodel != SHADE_BANDED) {
        length = curgeom->numelements;
        glBegin(GL_TRIANGLES);

        float activationval;
        for (loop2 = 0; loop2 < length; loop2++) {
            if (curmesh->shadingmodel == SHADE_GOURAUD) {
                // avoid repeating code 3 times
                for (loop3 = 0; loop3 < 3; loop3++) {
                    index = curgeom->elements[loop2][loop3];
                    if (cursurf->activationvals[index] == UNUSED_DATA)
                        break;
                }
                if (loop3 < 3)
                    // we have "UNUSED_DATA" on a node in this triangle, so don't draw here
                    continue;
                for (loop3 = 0; loop3 < 3; loop3++) {
                    index = curgeom->elements[loop2][loop3];
                    activationval = cursurf->activationvals[index];

                    if (use_textures)
                    {
                        glColor4f(1,1,1,0.4);
                        glEnable(GL_TEXTURE_1D);
                        if (curmesh->cmap->type == RAINBOW_CMAP){
                            UseTexture(map3d_info.rainbow_texture);
                        }
                        else
                            UseTexture(map3d_info.jet_texture);

                        glTexCoord1f(getContNormalizedValue(activationval, minactivation, maxactivation, curmesh->invert));
                    }


                    glNormal3fv(ptnormals[index]);
                    glVertex3fv(modelpts[index]);
                }
            }
            else {
                mean = 0;
                for (loop3 = 0; loop3 < 3; loop3++) {
                    index = curgeom->elements[loop2][loop3];
                    activationval = cursurf->activationvals[index];
                    if (activationval == UNUSED_DATA)
                        break;
                    mean += activationval;
                }
                if (loop3 < 3)
                    // we have "UNUSED_DATA" on a node in this triangle, so don't draw here
                    continue;

                mean /= 3;
                getContColor(mean, minactivation, maxactivation, curmesh->cmap, color, curmesh->invert);
                glColor4ub(color[0],color[1],color[2],color[3]);
                glNormal3fv(fcnormals[loop2]);

                for (loop3 = 0; loop3 < 3; loop3++) {
                    index = curgeom->elements[loop2][loop3];
                    glVertex3fv(modelpts[index]);
                }
            }
        }
        glEnd();
    }
    else if (curgeom->elementsize == 4 && curmesh->shadingmodel != SHADE_BANDED) {

        length = curgeom->numelements;
        glBegin(GL_TRIANGLES);
        for (loop2 = 0; loop2 < length; loop2++) {
            // this inner loop is a hack to avoid repeating the
            // following index/glNormal/glVertex code 4 times
            for (loop3 = 0; loop3 < 4; loop3++) {
                int idx1, idx2, idx3;
                if (loop3 == 3) {
                    idx1 = 1;
                    idx2 = 3;
                    idx3 = 2;
                }
                else if (loop3 == 2) {
                    idx1 = 0;
                    idx2 = loop3;
                    idx3 = 1;
                }
                else {
                    idx1 = 0;
                    idx2 = loop3;
                    idx3 = loop2 + 1;
                }
                if (curmesh->shadingmodel == SHADE_GOURAUD) {
                    index = curgeom->elements[loop2][idx1];
                    glNormal3fv(ptnormals[index]);
                    glVertex3fv(modelpts[index]);
                    index = curgeom->elements[loop2][idx2];
                    glNormal3fv(ptnormals[index]);
                    glVertex3fv(modelpts[index]);
                    index = curgeom->elements[loop2][idx3];
                    glNormal3fv(ptnormals[index]);
                    glVertex3fv(modelpts[index]);
                }
                else {
                    glNormal3fv(fcnormals[loop2]);
                    glVertex3fv(modelpts[curgeom->elements[loop2][idx1]]);
                    glVertex3fv(modelpts[curgeom->elements[loop2][idx2]]);
                    glVertex3fv(modelpts[curgeom->elements[loop2][idx3]]);
                }
            }
        }

        glEnd();
    }
    glDisable(GL_TEXTURE_1D);
#if SHOW_OPENGL_ERRORS
    GLenum e = glGetError();
    if (e)
        printf("GeomWindow DrawSurf OpenGL Error: %s\n", gluErrorString(e));
#endif
}





void ActivationMapWindow::addMesh(Mesh_Info *curmesh)
{
  /* copy from meshes to this window's mesh list */
  meshes.push_back(curmesh);
  curmesh->actipriv = this;
  recalcMinMax();

  // if this is the first mesh, copy vfov to the window and the
  // rotation quaternion to the clipping planes (these could have
  // been set by the command line).
  if (meshes.size() == 1) {
    vfov = curmesh->mysurf->vfov;
    clip->bd.qNow = curmesh->tran->rotate.qNow;
    Qt_ToMatrix(Qt_Conj(clip->bd.qNow), clip->bd.mNow);
    Ball_EndDrag(&clip->bd);



    // copy surf's bg/fg color
    bgcolor[0] = curmesh->mysurf->colour_bg[0] / 255.f;
    bgcolor[1] = curmesh->mysurf->colour_bg[1] / 255.f;
    bgcolor[2] = curmesh->mysurf->colour_bg[2] / 255.f;
    fgcolor[0] = curmesh->mysurf->colour_fg[0] / 255.f;
    fgcolor[1] = curmesh->mysurf->colour_fg[1] / 255.f;
    fgcolor[2] = curmesh->mysurf->colour_fg[2] / 255.f;
    large_font = (float)curmesh->mysurf->large_font;
    med_font = (float)curmesh->mysurf->med_font;
    small_font = (float)curmesh->mysurf->small_font;

    if (curmesh->mysurf->showinfotext != -1) showinfotext = curmesh->mysurf->showinfotext;

  }

  // make legend window's fg/bg equal to this one
  LegendWindow* lw = curmesh->legendwin;

  if (lw) {
    lw->bgcolor[0] = bgcolor[0];
    lw->bgcolor[1] = bgcolor[1];
    lw->bgcolor[2] = bgcolor[2];
    lw->fgcolor[0] = fgcolor[0];
    lw->fgcolor[1] = fgcolor[1];
    lw->fgcolor[2] = fgcolor[2];
  }
}

void ActivationMapWindow::recalcMinMax()
{
  xmin = ymin = zmin = FLT_MAX;
  xmax = ymax = zmax = -FLT_MAX;

  for (unsigned i = 0; i < meshes.size(); i++) {
    Mesh_Info* curmesh = meshes[i];
    xmin = MIN(xmin, curmesh->geom->xmin);
    ymin = MIN(ymin, curmesh->geom->ymin);
    zmin = MIN(zmin, curmesh->geom->zmin);
    xmax = MAX(xmax, curmesh->geom->xmax);
    ymax = MAX(ymax, curmesh->geom->ymax);
    zmax = MAX(zmax, curmesh->geom->zmax);
  }

  float xsize = xmax - xmin;
  float ysize = ymax - ymin;
  float zsize = zmax - zmin;
  xcenter = xsize / 2.f + xmin;
  ycenter = ysize / 2.f + ymin;
  zcenter = zsize / 2.f + zmin;

  // Set the "fit" for the window.  If -ss is specified, set
  // all windows' fit to the first window's.  If it's the first
  // window, set it only once.
  ActivationMapWindow* first_geom_window = GetActivationMapWindow(0);
  bool lock_l2norms = map3d_info.same_scale;
  if (!lock_l2norms || (this == first_geom_window && l2norm == 0))
    l2norm = sqrt(xsize * xsize + ysize * ysize + zsize * zsize);
  else if (lock_l2norms && this != first_geom_window)
    l2norm = first_geom_window->l2norm;

  qDebug() << l2norm;

  /* Adjust clipping plane coordinates */
  clip->front_init = clip->front = zmax - zsize / 4;
  clip->back_init = clip->back = -zmin - zsize / 4;
  clip->step = zsize / 200;
  clip->frontmax = zmax + clip->step;
  clip->backmax = -zmin + clip->step;
}

void ActivationMapWindow::mousePressEvent(QMouseEvent * event)
{
    setMoveCoordinates(event);
    HandleButtonPress(event, (float)event->x() / (float)width(), (float)event->y() / (float)height());
}



void ActivationMapWindow::mouseMoveEvent(QMouseEvent* event)
{
    HandleMouseMotion(event, (float)event->x() / (float)width(), (float)event->y() / (float)height());
}


void ActivationMapWindow::mouseReleaseEvent(QMouseEvent * event)
{
    HandleButtonRelease(event, (float)event->x() / (float)width(),(float)event->y() / (float)height());
}

void ActivationMapWindow::closeEvent(QCloseEvent * event)
{
        close();
 }


void ActivationMapWindow::HandleButtonPress(QMouseEvent * event, float xn, float yn)
{
    int button = mouseButtonOverride(event);
    int newModifiers = button == event->buttons() ? event->modifiers() : Qt::NoModifier;
    int x = int (width() * xn);
    int y = int (height() - height() * yn);

    last_xn = xn;
    last_yn = yn;

    int length = meshes.size();
    int loop = 0;
    Transforms *tran = 0;
    HVect vNow;

    for (loop = 0; loop < length; loop++) {
        tran = meshes[loop]->tran;
        // MIDDLE MOUSE DOWN + SHIFT = start rotate clipping planes
        if (button == Qt::MidButton && matchesModifiers(newModifiers, Qt::ShiftModifier, true)) {
            if ((clip->back_enabled || clip->front_enabled) &&!clip->lock_with_object) {
                vNow.x = 2.0f * x / width() - 1;
                vNow.y = 2.0f * y / height() - 1;
                Ball_Mouse(&clip->bd, vNow);
                Ball_BeginDrag(&clip->bd);
                break;
            }
#ifdef ROTATING_LIGHT
            else {
                vNow.x = 2.0f * x / width() - 1;
                vNow.y = 2.0f * y / height() - 1;
                Ball_Mouse(&light_pos, vNow);
                Ball_BeginDrag(&light_pos);
                break;
            }
#endif
        }
        if (button == Qt::LeftButton) {
            vNow.x = 2.0f * x / width() - 1.0f;
            vNow.y = 2.0f * y / height() - 1.0f;
            Ball_Mouse(&tran->rotate, vNow);
            Ball_BeginDrag(&tran->rotate);
            if (clip->lock_with_object) {
                Ball_Mouse(&clip->bd, vNow);
                Ball_BeginDrag(&clip->bd);
            }
        }
    }
    update();
}


void ActivationMapWindow::HandleMouseMotion(QMouseEvent * event, float xn, float yn)
{
    int button = mouseButtonOverride(event);
    int newModifiers = button == event->buttons() ? event->modifiers() : Qt::NoModifier;
    int x = int (width() * xn);
    int y = int (height() - height() * yn);

    int length = meshes.size();
    int loop = 0;
    Transforms *tran = 0;
    Mesh_Info *mesh = 0;

    if (length > 1 && !map3d_info.lockrotate)
        if (!map3d_info.lockgeneral) {
            loop = dominantsurf;
            length = loop + 1;
        }
        else {
            loop = secondarysurf;
            length = loop + 1;
        }

    for (; loop < length; loop++) {
        mesh = meshes[loop];
        if (map3d_info.selected_group != -1 && mesh->groupid != map3d_info.selected_group)
            continue;
        tran = mesh->tran;

        /* CTRL = nothing */
        if (matchesModifiers(newModifiers, Qt::ControlModifier, true)) {
            return;
        }

        /* MIDDLE MOUSE DOWN + SHIFT = rotate clipping planes */
        else if (button == Qt::MidButton && matchesModifiers(newModifiers, Qt::ShiftModifier, true)) {
            if ((clip->back_enabled || clip->front_enabled) &&!clip->lock_with_object) {
                HVect vNow;
                vNow.x = 2.0f * x / width() - 1.0f;
                vNow.y = 2.0f * y / height() - 1.0f;

                Ball_Mouse(&clip->bd, vNow);
                Ball_Update(&clip->bd, 0);
                break;
            }
            else {
                HVect vNow;
                vNow.x = 2.0f * x / width() - 1.0f;
                vNow.y = 2.0f * y / height() - 1.0f;

#ifdef ROTATING_LIGHT
                Ball_Mouse(&light_pos, vNow);
                Ball_Update(&light_pos, 0);
#endif
                break;
            }
        }
        // LEFT MOUSE DOWN + ALT = draw moving window
        else if (button == Qt::LeftButton && matchesModifiers(newModifiers, Qt::AltModifier, true)) {
            moveEvent(event);
        }
        // MIDDLE MOUSE DOWN + ALT = draw reshaping window
        else if (button == Qt::MidButton && matchesModifiers(newModifiers, Qt::AltModifier, true)) {
            sizeEvent(event);
        }
        // LEFT MOUSE DOWN + SHIFT = translate
        else if (button == Qt::LeftButton && matchesModifiers(newModifiers, Qt::ShiftModifier, true)) {
            tran->tx += l2norm * (xn - last_xn)  * vfov / 29.f;
            tran->ty += l2norm * (last_yn - yn)  * vfov / 29.f;

            //set the globalSurf translation
            mesh->mysurf->parent->SurfList[MAX_SURFS]->translation[0] = tran->tx;
            mesh->mysurf->parent->SurfList[MAX_SURFS]->translation[1] = tran->ty;
            mesh->mysurf->parent->SurfList[MAX_SURFS]->translation[2] = tran->tz;

        }
        // LEFT MOUSE DOWN = rotate
        else if (button == Qt::LeftButton) {
            HVect vNow;
            vNow.x = 2.0f * x / width() - 1.0f;
            vNow.y = 2.0f * y / height() - 1.0f;

            Ball_Mouse(&tran->rotate, vNow);
            Ball_Update(&tran->rotate, 0);

            //set the globalSurf translation
            mesh->mysurf->parent->SurfList[MAX_SURFS]->rotationQuat = tran->rotate.qNow;

            if (clip->lock_with_object) {
                Ball_Mouse(&clip->bd, vNow);
                Ball_Update(&clip->bd, 0);
            }
        }

        /* MIDDLE MOUSE DOWN = zoom (scale) */
        else if (button == Qt::MidButton) {
            if (yn < last_yn)
                vfov -= vfov / 24.0f;
            else if (yn > last_yn)
                vfov += vfov / 24.0f;

            if (vfov > 179)
                vfov = 179.0f;
            if (vfov < 0.01)
                vfov = 0.01f;
        }
    }

    last_xn = xn;
    last_yn = yn;

    update();
}

void ActivationMapWindow::HandleButtonRelease(QMouseEvent * event, float /*xn*/, float /*yn*/)
{
    int button = mouseButtonOverride(event);
    int newModifiers = button == event->button() ? event->modifiers() : Qt::NoModifier;

    int length = meshes.size();
    int loop = 0;
    Transforms *tran = 0;

    for (loop = 0; loop < length; loop++) {
        tran = meshes[loop]->tran;
        // MIDDLE MOUSE UP + SHIFT = end rotate clipping planes
        if (button == Qt::MidButton && matchesModifiers(newModifiers, Qt::ShiftModifier, true)) {
            if ((clip->back_enabled || clip->front_enabled) &&!clip->lock_with_object)
                Ball_EndDrag(&clip->bd);
#ifdef ROTATING_LIGHT
            else
                Ball_EndDrag(&light_pos);
#endif
            break;
        }
        // LEFT MOUSE UP = end rotate
        if (button == Qt::LeftButton) {
            Ball_EndDrag(&tran->rotate);
            if (clip->lock_with_object)
                Ball_EndDrag(&clip->bd);
        }
    }
    update();
}

void ActivationMapWindow::Transform(Mesh_Info * curmesh, float factor, bool compensateForRetinaDisplay)
{
    HMatrix mNow, cNow;           // arcball rotation matrices

    GLdouble front_plane[] = { 0, 0, 1, clip->front };
    GLdouble back_plane[] = { 0, 0, -1, clip->back };


    int pixelFactor = 1;

    if (compensateForRetinaDisplay)
    {
        pixelFactor=QApplication::desktop()->devicePixelRatio();
        // this compensates for the "Retina" display ratio.  See http://doc.qt.io/qt-5/highdpi.html
        //  (for some reason the picking doesn't need this)
    }
    glViewport(0, 0, width()*pixelFactor, height()*pixelFactor);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(vfov, width() / (float)height(), l2norm, 3 * l2norm);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* get the arcall rotation */
    Ball_Value(&curmesh->tran->rotate, mNow);
    Ball_Value(&clip->bd, cNow);

    /* current mousing translation */
    glTranslatef(curmesh->tran->tx, curmesh->tran->ty, curmesh->tran->tz);

    /* finally, move the mesh to in front of the eye */
    glTranslatef(0, 0, l2norm * (factor - 2));

    /* draw clipping planes (if enabled) */
    glPushMatrix();
    glMultMatrixf((float *)cNow);
    glTranslatef(xcenter, ycenter, zcenter);

    glClipPlane(GL_CLIP_PLANE0, front_plane);
    glClipPlane(GL_CLIP_PLANE1, back_plane);

    glPopMatrix();

    /* include the arcball rotation */
    glMultMatrixf((float *)mNow);

    /* move center of mesh to origin */
    glTranslatef(-xcenter, -ycenter, -zcenter);
}

void ActivationMapWindow::DrawBGImage()
{
    if (map3d_info.gi->bgcoords[0] != 0 || map3d_info.gi->bgcoords[3] != 1) {
        // user used a manual orientation - line it up as such
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(vfov, width() / (float)height(), l2norm, 3 * l2norm);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0, 0, -2 * l2norm);
        glTranslatef(-xcenter, -ycenter, -zcenter);
    }
    else {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, 1, 0, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
    float* pmin = &map3d_info.gi->bgcoords[0];
    float* pmax = &map3d_info.gi->bgcoords[3];

    UseTexture(map3d_info.bg_texture);

    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);  glVertex3f(pmin[0], pmin[1], pmin[2]);
    glTexCoord2f(0, 1);  glVertex3f(pmin[0], pmax[1], pmax[2]);
    glTexCoord2f(1, 1);  glVertex3f(pmax[0], pmax[1], pmax[2]);
    glTexCoord2f(1, 0);  glVertex3f(pmax[0], pmin[1], pmin[2]);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glClear(GL_DEPTH_BUFFER_BIT);

}





