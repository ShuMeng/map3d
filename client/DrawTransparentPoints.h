#ifndef DRAWTRANSPARENTPOINTS_H
#define DRAWTRANSPARENTPOINTS_H

#include "ui_DrawTransparentPoints.h"
#include "dialogs.h"
#include <QList>

class QPushButton;
class QDoubleSpinBox;
class QCheckBox;


class DrawTransparentPoints : public QDialog, public Ui::DrawTransparentPoints
{
    Q_OBJECT;

public:
    DrawTransparentPoints();

public slots:
  void on_applyButton_clicked ();
  void on_cancelButton_clicked ();
  void Transp_Points_Callback();
  void Activation_Callback();

  void CalculateMFSTransformMatrix(Mesh_Info * recordingmesh, Mesh_Info * curmesh);


  void CalculateActivation(Mesh_Info * curmesh);

  bool checkArray(Surf_Data* data, float *matrixvals);

  void InDeflateMesh(Mesh_Info * curmesh);

  void Recal_MFS_Callback();

private:

  QList<bool> origFixedTranparent;
  QList<bool> origPointsOnlyFix;

  QList<bool> origForward;
  QList<bool> origDatacloud;
  QList<bool> origMFS;


  QList<bool> origChangesize;
  QList<double> origInDeflate;


  QList<Mesh_Info*> meshes;

  // widgets

  QList<QCheckBox*> fixedPointsOnlyBoxes;
  QList<QCheckBox*> fixedTransparentBoxes;
  QList<QCheckBox*> fixedDatacloudBoxes;
  QList<QCheckBox*> fixedForwardBoxes;
  QList<QCheckBox*> fixedMFSBoxes;

  QList<QPushButton*> ActivationButton;

  QList<QCheckBox*> fixedSizeBoxes;
  QList<QDoubleSpinBox*> InDeflateBoxes;



};

#if 0

//void Transp_PointsDialogCreate(bool show = true);
//void Transp_PointsCancel();
//void Transp_PointsPreview(bool okay);
//void Transp_PointsOkay();
//void Transp_Pointscallback(FilesDialogRowData* rowdata);
//void Transp_PointsDialogChangeLock();
//void Transp_Pointsdestroycallback();


//void updateTransp_PointsDialogValues(Mesh_Info* mesh);

#endif


#endif // DRAWTRANSPARENTPOINTS_H
