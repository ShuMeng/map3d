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

#include "ActivationMapWindow.h"
#include <QPushButton>



extern Map3d_Info map3d_info;

#include <iostream>

using namespace std;

int unlock_transparency_surfnum[30];
int unlock_electrode_surfnum[30];

const char* MeshProperty_trans_Points = "MeshProperty_trans_Points";

enum contTableCols{
    SurfNum, Transparencycol, PointsOnlyCols, ActivationCols
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


        if (mesh->data)
        {
            origPointsOnly = mesh->data->user_pointsonly;
            origtransparent = mesh->data->user_transparent;
        }

        origPointsOnlyFix << origPointsOnly;
        origFixedTranparent << origtransparent;


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

        connect(fixedPoints , SIGNAL(toggled(bool)), this, SLOT(Transp_Points_Callback()));
        connect(fixedTrans, SIGNAL(toggled(bool)), this, SLOT(Transp_Points_Callback()));
        connect(fixedbutton, SIGNAL(clicked()), this, SLOT(Activation_Callback()));

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
        }

        Broadcast(MAP3D_UPDATE);
}


void DrawTransparentPoints::Activation_Callback()

{

    Q_ASSERT(sender());
    QVariant rowProp = sender()->property(MeshProperty_trans_Points);
    int row = rowProp.toInt();
    Mesh_Info* mesh = meshes[row];
    if (mesh->data) {

        ActivationMapWindow* actimwin;
        actimwin = ActivationMapWindow::ActivationMapWindowCreate(0,0,0,0);
        actimwin->addMesh(mesh);
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


