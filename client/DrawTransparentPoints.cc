#include "DrawTransparentPoints.h"
#include "MeshList.h"
#include "Surf_Data.h"
#include "Map3d_Geom.h"
#include "WindowManager.h"
#include "eventdata.h"
#include <math.h>
#include <QCheckBox>
#include "FileDialog.h"
#include "MainWindow.h"
#include "ProcessCommandLineOptions.h"
#include "Transforms.h"
#include "eventdata.h"
#include "map3d-struct.h"
#include "matlabarray.h"
#include "GetMatrixSlice.h"
#include "ActivationLegendWindow.h"

#include "ActivationMapWindow.h"
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>

#include <iostream>
using namespace std;

#include <algorithm>
#include <vector>
#include <cmath>
#include <tuple>

#include <functional>

#include <QDebug>
#include <engine.h>
#include <matrix.h>
#include <mex.h>
#include "map3dmath.h"
#include <cstdlib>

#include <fstream>
#include <sstream>

extern Map3d_Info map3d_info;
extern int  maxactivation, minactivation;


int unlock_transparency_surfnum[30];
int unlock_electrode_surfnum[30];
int unlock_datacloud_surfnum[30];
int unlock_forward_surfnum[30];
int unlock_MFS_surfnum[30];

const char* MeshProperty_trans_Points = "MeshProperty_trans_Points";

Engine *ep_matrix = engOpen(NULL);

enum contTableCols{
    SurfNum, Transparencycol, PointsOnlyCols, ActivationCols, DatacloudCols, ForwardCols, MFSCols, ChangeSizeCol, InDeflateCols
};


DrawTransparentPoints::DrawTransparentPoints()
{
    setupUi(this);
    int row=1;

    for (MeshIterator mi; !mi.isDone(); ++mi, ++row)
    {
        Mesh_Info* mesh = mi.getMesh();
        int index = row-1;

        // FIX - subsurf, NULL data

        bool origPointsOnly = false;
        bool origtransparent = false;
        bool origDatacloudIni = false;
        bool origForwardIni = false;
        bool origMFSIni = false;
        bool origSize =false;
        float origInDeIni=1;

        if (mesh->data)
        {
            origPointsOnly = mesh->data->user_pointsonly;
            origtransparent = mesh->data->user_transparent;
            origDatacloudIni = mesh->data->user_datacloud;
            origForwardIni = mesh->data->user_forward;
            origMFSIni = mesh->data->user_MFS;
            origSize =mesh->data->user_fixmeshsize;
            origInDeIni=mesh->data->user_InDe_parameter;

        }

        origPointsOnlyFix << origPointsOnly;
        origFixedTranparent << origtransparent;
        origForward << origForwardIni;
        origDatacloud << origDatacloudIni;
        origMFS << origMFSIni;
        origChangesize << origSize;
        origInDeflate << origInDeIni;

        meshes << mesh;

        QLabel* label = new QLabel(QString::number(mesh->geom->surfnum), this);
        gridLayout->addWidget(label, row, SurfNum);

        QCheckBox* fixedPoints = new QCheckBox(this);
        fixedPoints->setChecked(origPointsOnly);
        fixedPoints->setProperty(MeshProperty_trans_Points, index);
        fixedPointsOnlyBoxes << fixedPoints;
        gridLayout->addWidget(fixedPoints, row, PointsOnlyCols);


        QCheckBox* fixedTrans = new QCheckBox(this);
        fixedTrans->setChecked(origtransparent);
        fixedTrans->setProperty(MeshProperty_trans_Points, index);
        fixedTransparentBoxes << fixedTrans;
        gridLayout->addWidget(fixedTrans, row, Transparencycol);

        QPushButton* fixedbutton =new QPushButton ("Activation map #" + QString::number(mesh->geom->surfnum), this);
        ActivationButton << fixedbutton;
        fixedbutton->setProperty(MeshProperty_trans_Points, index);
        gridLayout->addWidget(fixedbutton, row, ActivationCols);

        QCheckBox* fixdatacloud = new QCheckBox(this);
        fixdatacloud->setChecked(origDatacloudIni);
        fixdatacloud->setProperty(MeshProperty_trans_Points, index);
        fixedDatacloudBoxes << fixdatacloud;
        gridLayout->addWidget(fixdatacloud, row, DatacloudCols);


        QCheckBox* fixforward = new QCheckBox(this);
        fixforward->setChecked(origForwardIni);
        fixforward->setProperty(MeshProperty_trans_Points, index);
        fixedForwardBoxes << fixforward;
        gridLayout->addWidget(fixforward, row, ForwardCols);


        QCheckBox* fixMFS = new QCheckBox(this);
        fixMFS->setChecked(origMFSIni);
        fixMFS->setProperty(MeshProperty_trans_Points, index);
        fixedMFSBoxes << fixMFS;
        gridLayout->addWidget(fixMFS, row, MFSCols);


        QCheckBox* fixedsize = new QCheckBox(this);
        fixedsize->setChecked(origSize);
        fixedsize->setProperty(MeshProperty_trans_Points, index);
        fixedSizeBoxes << fixedsize;
        gridLayout->addWidget(fixedsize, row, ChangeSizeCol);


        QDoubleSpinBox* InDe = new QDoubleSpinBox(this);
        InDe->setRange(0.1, 10);
        InDe->setSingleStep(0.1);
        InDe->setValue(origInDeIni);
        InDe->setProperty(MeshProperty_trans_Points, index);
        InDeflateBoxes << InDe;
        gridLayout->addWidget(InDe, row, InDeflateCols);


        connect(fixedPoints , SIGNAL(toggled(bool)), this, SLOT(Transp_Points_Callback()));
        connect(fixedTrans, SIGNAL(toggled(bool)), this, SLOT(Transp_Points_Callback()));
        connect(fixedbutton, SIGNAL(clicked()), this, SLOT(Activation_Callback()));
        connect(fixdatacloud, SIGNAL(toggled(bool)), this, SLOT(Transp_Points_Callback()));
        connect(fixforward, SIGNAL(toggled(bool)), this, SLOT(Transp_Points_Callback()));
        connect(fixMFS, SIGNAL(toggled(bool)), this, SLOT(Transp_Points_Callback()));
        connect(fixedsize, SIGNAL(toggled(bool)), this, SLOT(Transp_Points_Callback()));

        connect(InDe, SIGNAL(valueChanged(double)), this, SLOT(Transp_Points_Callback()));

    }
}

void DrawTransparentPoints::Transp_Points_Callback()
{    Q_ASSERT(sender());

     QVariant rowProp = sender()->property(MeshProperty_trans_Points);

      int row = rowProp.toInt();
       Mesh_Info* mesh = meshes[row];

        if (mesh->data) {

            if (fixedPointsOnlyBoxes[row]->isChecked())
            {
                mesh->data->user_pointsonly = true;
                unlock_electrode_surfnum[row]=row+1;
            }

            else {
                mesh->data->user_pointsonly = false;
                unlock_electrode_surfnum[row]=0;
            }


            if (fixedTransparentBoxes[row]->isChecked())
            {
                mesh->data->user_transparent = true;
                unlock_transparency_surfnum[row]=row+1;
            }
            else {
                mesh->data->user_transparent = false;
                unlock_transparency_surfnum[row]=0;
            }


            if (fixedDatacloudBoxes[row]->isChecked())
            {
                mesh->data->user_datacloud = true;
                unlock_datacloud_surfnum[row]=row+1;
            }
            else {
                mesh->data->user_datacloud = false;
                unlock_datacloud_surfnum[row]=0;
            }


            if (fixedForwardBoxes[row]->isChecked())
            {
                mesh->data->user_forward = true;
                unlock_forward_surfnum[row]=row+1;

            }
            else {
                mesh->data->user_forward = false;
                unlock_forward_surfnum[row]=0;
            }


            if (fixedMFSBoxes[row]->isChecked())
            {

                mesh->data->user_MFS = true;
                unlock_MFS_surfnum[row]=row+1;


                int length = meshes.size();

                if ((length>1) && (row-1>=0))
                {
                    Mesh_Info *recordingmesh = 0;
                    recordingmesh=meshes[row-1];

                    CalculateMFSTransformMatrix(recordingmesh,mesh);

                }

            }
            else {
                mesh->data->user_MFS = false;
                unlock_MFS_surfnum[row]=0;
            }


            if (fixedSizeBoxes[row]->isChecked())

            {
                mesh->data->user_fixmeshsize = true;
                mesh->data->user_InDe_parameter=(float)InDeflateBoxes[row]->value();
                InDeflateMesh(mesh);


                // only change catheter size.


                Mesh_Info *sourcemesh = 0;
                sourcemesh=meshes[row+1];
                CalculateMFSTransformMatrix(mesh,sourcemesh);


            }
            else {
                mesh->data->user_fixmeshsize = false;
            }
        }

        Broadcast(MAP3D_UPDATE);
}




void DrawTransparentPoints::InDeflateMesh(Mesh_Info * curmesh)

{


    Map3d_Geom *curgeom = 0;
    Surf_Data *cursurf = 0;
    curgeom = curmesh->geom;
    cursurf = curmesh->data;

    int  meshpoint_num =0;
    meshpoint_num = curgeom->numpts;

    float** pts = curgeom->points[curgeom->geom_index];


    double sum_x,sum_y,sum_z,center_x,center_y,center_z;

    for (int i=0; i< meshpoint_num; i++)
    {
        sum_x += pts[i][0];
        sum_y += pts[i][1];
        sum_z += pts[i][2];

        //std::cout<<"pts x  "<<pts[i][1]<<std::endl;

    }

    //std::cout<<"pts y  "<<pts[0][1]<<std::endl;


    center_x = (sum_x)/meshpoint_num;
    center_y = (sum_y)/meshpoint_num;
    center_z = (sum_z)/meshpoint_num;


    std::cout<<"sun_x  "<<sum_x<<"    "<<"center_x   "<<center_x<<std::endl;

    std::cout<<"sun_y  "<<sum_y<<"    "<<"center_y   "<<center_y<<std::endl;

    std::cout<<"sun_z  "<<sum_z<<"    "<<"center_z   "<<center_z<<std::endl;

    std::cout<<"---------------------------------------------------------------------------"<<std::endl;


    float **InDeflated_pts = 0;
    InDeflated_pts= Alloc_fmatrix(curgeom->numpts, 3);


    for (int j=0; j< meshpoint_num; j++)
    {
    InDeflated_pts[j][0] = pts[j][0]+(curmesh->data->user_InDe_parameter-1)*(pts[j][0]-center_x);
    InDeflated_pts[j][1] = pts[j][1]+(curmesh->data->user_InDe_parameter-1)*(pts[j][1]-center_y);
    InDeflated_pts[j][2] = pts[j][2]+(curmesh->data->user_InDe_parameter-1)*(pts[j][2]-center_z);
    }


    curgeom->points[curgeom->geom_index]=InDeflated_pts;

   // std::cout<<"InDeflated_pts  "<<InDeflated_pts[0][1]<<std::endl;



}





bool DrawTransparentPoints::checkArray(Surf_Data* data, float *matrixvals)

{
    long  leadnum;

    for (leadnum = 0; leadnum < data->numleads; leadnum++) {

        if(matrixvals[leadnum] != 0)
        {
            return false;
        }
    }
    return true;
}



void DrawTransparentPoints::Activation_Callback()

{
    Q_ASSERT(sender());
    QVariant rowProp = sender()->property(MeshProperty_trans_Points);
    int row = rowProp.toInt();

    QWidget *actiWidget;
    QHBoxLayout *gLayout;
    actiWidget = new QWidget();

    gLayout = new QHBoxLayout(actiWidget);

    Mesh_Info* mesh = meshes[row];
    Surf_Data* data = mesh->data;

    CalculateActivation(mesh);


    if (checkArray(data,data->activationvals)==0)

    {

        ActivationMapWindow* actiwin;
        actiwin = new ActivationMapWindow(actiWidget);
        //actiwin = ActivationMapWindow::ActivationMapWindowCreate(0,0,0,0);
        actiwin->addMesh(mesh);
        actiwin->setWindowFlags(Qt::WindowTransparentForInput);


        Surf_Data *s=0;
        s=mesh->data;

        /* create colormap legend window */
        ActivationLegendWindow *lpriv = NULL;
        lpriv = new ActivationLegendWindow(actiWidget);

        int width, height;
        width = mesh->lw_xmax - mesh->lw_xmin;
        height = mesh->lw_ymax - mesh->lw_ymin;
        //lpriv = ActivationLegendWindow::ActivationLegendWindowCreate(mesh, width, height, mesh->lw_xmin, mesh->lw_ymin, !mesh->showlegend);


        gLayout->addWidget(actiwin);
        gLayout->setStretch(0,3);
        gLayout->addWidget(lpriv);
        gLayout->setStretch(1,1);

        lpriv->setVisible(true);
        actiwin->show();

        actiWidget->setMinimumSize(500,380);
        actiWidget->show();


        if (lpriv != NULL) {
            // can fail if more than MAX_SURFS l-wins.
            lpriv->orientation = 1;
            if (mesh->mysurf->legendticks != -1) {
                lpriv->nticks = mesh->mysurf->legendticks;
                lpriv->matchContours = true;
            }

            lpriv->surf = s;
            lpriv->mesh = mesh;
            lpriv->map = &mesh->cmap;


            // background color
            lpriv->bgcolor[0] = mesh->mysurf->colour_bg[0] / 255.f;
            lpriv->bgcolor[1] = mesh->mysurf->colour_bg[1] / 255.f;
            lpriv->bgcolor[2] = mesh->mysurf->colour_bg[2] / 255.f;
            lpriv->fgcolor[0] = mesh->mysurf->colour_fg[0] / 255.f;
            lpriv->fgcolor[1] = mesh->mysurf->colour_fg[1] / 255.f;
            lpriv->fgcolor[2] = mesh->mysurf->colour_fg[2] / 255.f;
        }
    }

    else {

        QMessageBox::warning(this,QString("Warning"),QString("No Activation times for this surface!"));
    }
}




void DrawTransparentPoints::CalculateActivation(Mesh_Info * curmesh)

{
    engSetVisible(ep_matrix, false);

    int  meshpoint_num =0;

    Map3d_Geom *curgeom = 0;
    Surf_Data *cursurf = 0;
    curgeom = curmesh->geom;
    cursurf = curmesh->data;
    meshpoint_num = curgeom->numpts;



    float** pts_atria = curgeom->points[curgeom->geom_index];

    double mesh_x[meshpoint_num],mesh_y[meshpoint_num],mesh_z[meshpoint_num];
    for (int i=0; i< meshpoint_num; i++)
    {
        mesh_x[i] =  pts_atria[i][0];
        mesh_y[i] =  pts_atria[i][1];
        mesh_z[i] =  pts_atria[i][2];
    }

    double pot_temp[meshpoint_num][curmesh->data->numframes];

    for (int i=0; i< meshpoint_num; i++)
    {
        for (int j=0; j< curmesh->data->numframes; j++)

            if (cursurf->inversevals[cursurf->framenum][i]==0)
            {pot_temp[i][j] =cursurf->potvals[j][i];}
            else
            {pot_temp[i][j] =cursurf->inversevals[j][i];}
    }


    mxArray *potential_matlab = mxCreateDoubleMatrix(curmesh->data->numframes,meshpoint_num, mxREAL);
    memcpy(mxGetPr(potential_matlab), pot_temp, meshpoint_num*curmesh->data->numframes*sizeof(double));
    engPutVariable(ep_matrix, "potential",potential_matlab);

    mxArray *x_matlab = mxCreateDoubleMatrix(1,meshpoint_num, mxREAL);
    memcpy(mxGetPr(x_matlab), mesh_x, meshpoint_num*sizeof(double));
    engPutVariable(ep_matrix, "c_x",x_matlab);

    mxArray *y_matlab = mxCreateDoubleMatrix(1,meshpoint_num, mxREAL);
    memcpy(mxGetPr(y_matlab), mesh_y, meshpoint_num*sizeof(double));
    engPutVariable(ep_matrix, "c_y",y_matlab);

    mxArray *z_matlab = mxCreateDoubleMatrix(1,meshpoint_num, mxREAL);
    memcpy(mxGetPr(z_matlab), mesh_z, meshpoint_num*sizeof(double));
    engPutVariable(ep_matrix, "c_z",z_matlab);

    engEvalString(ep_matrix, "addpath(genpath('/hpc_ntot/smen974/Map3d/MFS_Functions'))");
    engEvalString(ep_matrix, "[activation]=ActivationCalculation(c_x,c_y,c_z, potential)");

    mxArray *activation_matlab = engGetVariable(ep_matrix, "activation");
    double *activation = mxGetPr(activation_matlab);


    for (int i=0; i< meshpoint_num; i++)
    {
        cursurf->activationvals[i] =activation[i];
    }

}

void DrawTransparentPoints::on_applyButton_clicked()
{
    Broadcast(MAP3D_UPDATE);
    close();
}

void DrawTransparentPoints::on_cancelButton_clicked()
{

    close();
}

void DrawTransparentPoints::CalculateMFSTransformMatrix(Mesh_Info * recordingmesh, Mesh_Info * curmesh)

{


    std::cout<<"enter CalculateMFSTransformMatrix"<<std::endl;

    engSetVisible(ep_matrix, false);

    int catheter_num = 0, atria_num =0, loop1 = 0,loop2 = 0;


    // float **modelpts,**atriapts;
    long **catheterelement, **atriaelement;


    Map3d_Geom *recordinggeom = 0;
    Surf_Data *recordingsurf = 0;
    recordinggeom = recordingmesh->geom;
    recordingsurf = recordingmesh->data;
    catheter_num = recordinggeom->numpts;
    // modelpts = recordinggeom->points[recordinggeom->geom_index];
    catheterelement = recordinggeom->elements;


    Map3d_Geom *curgeom = 0;
    Surf_Data *cursurf = 0;
    curgeom = curmesh->geom;
    cursurf = curmesh->data;
    atria_num = curgeom->numpts;
    // atriapts = curgeom->points[curgeom->geom_index];
    atriaelement = curgeom->elements;

    // this part is to rotate the catheter. if map3d_info.lockrotate==LOCK_OFF, only apply transform matrix to catheter
    // if map3d_info.lockrotate==LOCK_FULL, apply both transform matrix to catheter and atrium, corresponding matrix is different.
    float** pts = recordinggeom->points[recordinggeom->geom_index];
    float** geom_temp_catheter_pts=pts;
    float **rotated_catheter_pts = 0;
    rotated_catheter_pts= Alloc_fmatrix(recordinggeom->numpts, 3);

    GeomWindow* priv_catheter = recordingmesh->gpriv;
    HMatrix mNow_catheter /*, original */ ;  // arcball rotation matrices
    Transforms *tran_catheter = recordingmesh->tran;
    //translation matrix in column-major
    float centerM_catheter[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},
                                    {-priv_catheter->xcenter,-priv_catheter->ycenter,-priv_catheter->zcenter,1}};
    float invCenterM_catheter[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},
                                       {priv_catheter->xcenter,priv_catheter->ycenter,priv_catheter->zcenter,1}};
    float translateM_catheter[4][4] = { {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0},
                                        {tran_catheter->tx, tran_catheter->ty, tran_catheter->tz, 1}
                                      };
    float temp_catheter[16];
    float product_catheter[16];

    //rotation matrix
    Ball_Value(&tran_catheter->rotate, mNow_catheter);
    // apply translation
    // translate recordingmesh's center to origin
    MultMatrix16x16((float *)translateM_catheter, (float *)invCenterM_catheter, (float*)product_catheter);
    // rotate
    MultMatrix16x16((float *)product_catheter, (float *)mNow_catheter, (float*)temp_catheter);
    // revert recordingmesh translation to origin
    MultMatrix16x16((float*)temp_catheter, (float *) centerM_catheter, (float*)product_catheter);



    for (loop1 = 0; loop1 < catheter_num; loop1++)
    {

        float rhs_catheter[4];
        float result_catheter[4];
        rhs_catheter[0] = pts[loop1][0];
        rhs_catheter[1] = pts[loop1][1];
        rhs_catheter[2] = pts[loop1][2];
        rhs_catheter[3] = 1;

        MultMatrix16x4(product_catheter, rhs_catheter, result_catheter);

        rotated_catheter_pts[loop1][0] = result_catheter[0];
        rotated_catheter_pts[loop1][1] = result_catheter[1];
        rotated_catheter_pts[loop1][2] = result_catheter[2];
    }

    geom_temp_catheter_pts=rotated_catheter_pts;

    //this part is to rotate the source surface (atrium).transform matrix is not applied if map3d_info.lockrotate==LOCK_OFF

    float** pts_atria = curgeom->points[curgeom->geom_index];
    float** geom_temp_atria_pts=pts_atria;
    float **rotated_atria_pts = 0;
    rotated_atria_pts= Alloc_fmatrix(curgeom->numpts, 3);


    GeomWindow* priv_atria = curmesh->gpriv;
    HMatrix mNow_atria /*, original */ ;  // arcball rotation matrices
    Transforms *tran_atria = curmesh->tran;
    //translation matrix in column-major
    float centerM_atria[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},
                                 {-priv_atria->xcenter,-priv_atria->ycenter,-priv_atria->zcenter,1}};
    float invCenterM_atria[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},
                                    {priv_atria->xcenter,priv_atria->ycenter,priv_atria->zcenter,1}};
    float translateM_atria[4][4] = { {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0},
                                     {tran_atria->tx, tran_atria->ty, tran_atria->tz, 1}
                                   };
    float temp_atria[16];
    float product_atria[16];

    //rotation matrix
    Ball_Value(&tran_atria->rotate, mNow_atria);
    // apply translation
    // translate curmesh's center to origin
    MultMatrix16x16((float *)translateM_atria, (float *)invCenterM_atria, (float*)product_atria);
    // rotate
    MultMatrix16x16((float *)product_atria, (float *)mNow_atria, (float*)temp_atria);
    // revert curmesh translation to origin
    MultMatrix16x16((float*)temp_atria, (float *) centerM_atria, (float*)product_atria);


    for (loop2 = 0; loop2 < atria_num; loop2++)
    {

        float rhs_atria[4];
        float result_atria[4];
        rhs_atria[0] = pts_atria[loop2][0];
        rhs_atria[1] = pts_atria[loop2][1];
        rhs_atria[2] = pts_atria[loop2][2];
        rhs_atria[3] = 1;

        MultMatrix16x4(product_atria, rhs_atria, result_atria);

        rotated_atria_pts[loop2][0] = result_atria[0];
        rotated_atria_pts[loop2][1] = result_atria[1];
        rotated_atria_pts[loop2][2] = result_atria[2];

    }
    geom_temp_atria_pts=rotated_atria_pts;



    // pass coordinates of catheters
    double pot_temp[catheter_num][recordingmesh->data->numframes], cath_x[catheter_num],cath_y[catheter_num],cath_z[catheter_num];

    for (int i=0; i< catheter_num; i++)
    {

        cath_x[i] =  geom_temp_catheter_pts[i][0];
        cath_y[i] =  geom_temp_catheter_pts[i][1];
        cath_z[i] =  geom_temp_catheter_pts[i][2];
    }


    for (int i=0; i< catheter_num; i++)
    {
        for (int j=0; j< recordingmesh->data->numframes; j++)

            if (recordingsurf->forwardvals[recordingsurf->framenum][i]==0)
            {pot_temp[i][j] =recordingsurf->potvals[j][i];}
            else
            {pot_temp[i][j] =recordingsurf->forwardvals[j][i];}
    }



    mxArray *catheter_potential_matlab = mxCreateDoubleMatrix(recordingmesh->data->numframes,catheter_num, mxREAL);
    memcpy(mxGetPr(catheter_potential_matlab), pot_temp, catheter_num*recordingmesh->data->numframes*sizeof(double));
    engPutVariable(ep_matrix, "catheter_potential",catheter_potential_matlab);


    mxArray *cath_x_matlab = mxCreateDoubleMatrix(1,catheter_num, mxREAL);
    memcpy(mxGetPr(cath_x_matlab), cath_x, catheter_num*sizeof(double));
    engPutVariable(ep_matrix, "c_x",cath_x_matlab);

    mxArray *cath_y_matlab = mxCreateDoubleMatrix(1,catheter_num, mxREAL);
    memcpy(mxGetPr(cath_y_matlab), cath_y, catheter_num*sizeof(double));
    engPutVariable(ep_matrix, "c_y",cath_y_matlab);

    mxArray *cath_z_matlab = mxCreateDoubleMatrix(1,catheter_num, mxREAL);
    memcpy(mxGetPr(cath_z_matlab), cath_z, catheter_num*sizeof(double));
    engPutVariable(ep_matrix, "c_z",cath_z_matlab);

    // pass coordinates of atria
    double atria_x[atria_num],atria_y[atria_num],atria_z[atria_num];
    for (int i=0; i< atria_num; i++)
    {

        atria_x[i] =  geom_temp_atria_pts[i][0];
        atria_y[i] =  geom_temp_atria_pts[i][1];
        atria_z[i] =  geom_temp_atria_pts[i][2];
    }
    mxArray *atria_x_matlab = mxCreateDoubleMatrix(1,atria_num, mxREAL);
    memcpy(mxGetPr(atria_x_matlab), atria_x, atria_num*sizeof(double));
    engPutVariable(ep_matrix, "a_x",atria_x_matlab);

    mxArray *atria_y_matlab = mxCreateDoubleMatrix(1,atria_num, mxREAL);
    memcpy(mxGetPr(atria_y_matlab), atria_y, atria_num*sizeof(double));
    engPutVariable(ep_matrix, "a_y",atria_y_matlab);

    mxArray *atria_z_matlab = mxCreateDoubleMatrix(1,atria_num, mxREAL);
    memcpy(mxGetPr(atria_z_matlab), atria_z, atria_num*sizeof(double));
    engPutVariable(ep_matrix, "a_z",atria_z_matlab);



    // pass elements of catheters
    double c_ele_1[recordinggeom->numelements],c_ele_2[recordinggeom->numelements],c_ele_3[recordinggeom->numelements];
    for (int j=0; j< recordinggeom->numelements; j++)
    {
        c_ele_1[j] = catheterelement[j][0]+1;
        c_ele_2[j] = catheterelement[j][1]+1;
        c_ele_3[j] = catheterelement[j][2]+1;
    }

    mxArray *cath_e1_matlab = mxCreateDoubleMatrix(1,recordinggeom->numelements, mxREAL);
    memcpy(mxGetPr(cath_e1_matlab), c_ele_1, recordinggeom->numelements*sizeof(double));
    engPutVariable(ep_matrix, "c_ele_1",cath_e1_matlab);

    mxArray *cath_e2_matlab = mxCreateDoubleMatrix(1,recordinggeom->numelements, mxREAL);
    memcpy(mxGetPr(cath_e2_matlab), c_ele_2, recordinggeom->numelements*sizeof(double));
    engPutVariable(ep_matrix, "c_ele_2",cath_e2_matlab);

    mxArray *cath_e3_matlab = mxCreateDoubleMatrix(1,recordinggeom->numelements, mxREAL);
    memcpy(mxGetPr(cath_e3_matlab), c_ele_3, recordinggeom->numelements*sizeof(double));
    engPutVariable(ep_matrix, "c_ele_3",cath_e3_matlab);

    // pass elements of atria
    double a_ele_1[curgeom->numelements],a_ele_2[curgeom->numelements],a_ele_3[curgeom->numelements];
    for (int k=0; k< curgeom->numelements; k++)
    {
        a_ele_1[k] = atriaelement[k][0]+1;
        a_ele_2[k] = atriaelement[k][1]+1;
        a_ele_3[k] = atriaelement[k][2]+1;

    }

    mxArray *atria_e1_matlab = mxCreateDoubleMatrix(1,curgeom->numelements, mxREAL);
    memcpy(mxGetPr(atria_e1_matlab), a_ele_1, curgeom->numelements*sizeof(double));
    engPutVariable(ep_matrix, "a_ele_1",atria_e1_matlab);

    mxArray *atria_e2_matlab = mxCreateDoubleMatrix(1,curgeom->numelements, mxREAL);
    memcpy(mxGetPr(atria_e2_matlab), a_ele_2, curgeom->numelements*sizeof(double));
    engPutVariable(ep_matrix, "a_ele_2",atria_e2_matlab);

    mxArray *atria_e3_matlab = mxCreateDoubleMatrix(1,curgeom->numelements, mxREAL);
    memcpy(mxGetPr(atria_e3_matlab), a_ele_3, curgeom->numelements*sizeof(double));
    engPutVariable(ep_matrix, "a_ele_3",atria_e3_matlab);


    engEvalString(ep_matrix, "addpath(genpath('/hpc_ntot/smen974/Map3d/MFS_Functions'))");
    engEvalString(ep_matrix, "mfsEGM=solve_MFS(c_x,c_y,c_z,c_ele_1,c_ele_2,c_ele_3,a_x,a_y,a_z,a_ele_1,a_ele_2,a_ele_3, catheter_potential)");

    mxArray *mfsEGM_matlab = engGetVariable(ep_matrix, "mfsEGM");
    double *mfsEGM = mxGetPr(mfsEGM_matlab);

    //    ofstream myfile;
    //    myfile.open ("inverse_LA_as_catheter.txt");

    for (int j=0; j< curmesh->data->numframes; j++)
    {
        for (int i=0; i< atria_num; i++)
        {
            cursurf->MFSvals[j][i] =mfsEGM[i+j*atria_num];

            //            myfile << cursurf->MFSvals[j][i];
            //            myfile << "\n";
            //            //myfile.close();

        }
    }
}

