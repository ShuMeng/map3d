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




extern Map3d_Info map3d_info;
extern int  maxactivation, minactivation;


int unlock_transparency_surfnum[30];
int unlock_electrode_surfnum[30];
int unlock_datacloud_surfnum[30];
int unlock_forward_surfnum[30];
int unlock_MFS_surfnum[30];

const char* MeshProperty_trans_Points = "MeshProperty_trans_Points";



enum contTableCols{
    SurfNum, Transparencycol, PointsOnlyCols, ActivationCols, DatacloudCols, ForwardCols, MFSCols
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

        if (mesh->data)
        {
            origPointsOnly = mesh->data->user_pointsonly;
            origtransparent = mesh->data->user_transparent;
            origDatacloudIni = mesh->data->user_datacloud;
            origForwardIni = mesh->data->user_forward;
            origMFSIni = mesh->data->user_MFS;

        }

        origPointsOnlyFix << origPointsOnly;
        origFixedTranparent << origtransparent;
        origForward << origDatacloudIni;
        origDatacloud << origForwardIni;
        origMFS << origMFSIni;

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


        connect(fixedPoints , SIGNAL(toggled(bool)), this, SLOT(Transp_Points_Callback()));
        connect(fixedTrans, SIGNAL(toggled(bool)), this, SLOT(Transp_Points_Callback()));
        connect(fixedbutton, SIGNAL(clicked()), this, SLOT(Activation_Callback()));
        connect(fixdatacloud, SIGNAL(toggled(bool)), this, SLOT(Transp_Points_Callback()));
        connect(fixforward, SIGNAL(toggled(bool)), this, SLOT(Transp_Points_Callback()));
        connect(fixMFS, SIGNAL(toggled(bool)), this, SLOT(Transp_Points_Callback()));

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

                int length = meshes.size();

                if ((length>1) && (row+1<length))
                {
                    Mesh_Info *sourcemesh = 0;
                    sourcemesh=meshes[row+1];
                    Map3d_Geom *sourcegeom = 0;
                    sourcegeom = sourcemesh->geom;

                    //                    if (sourcegeom->numdatacloud==0)

                    //                    {
                    //                        QMessageBox::warning(this,QString("Warning"),QString("Provide values for internal datacloud"));
                    //                    }
                }

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
                    Map3d_Geom *recordinggeom = 0;
                    recordinggeom = recordingmesh->geom;

                }

            }
            else {
                mesh->data->user_forward = false;
                unlock_forward_surfnum[row]=0;
            }





        }

        Broadcast(MAP3D_UPDATE);
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
    if (mesh->data->activationvals[0]!=0) {

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



void DrawTransparentPoints::on_applyButton_clicked()
{
    Broadcast(MAP3D_UPDATE);
    close();
}

void DrawTransparentPoints::on_cancelButton_clicked()
{

    close();
}


