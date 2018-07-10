#ifndef DRAWTRANSPARENTPOINTS_H
#define DRAWTRANSPARENTPOINTS_H

#include "ui_DrawTransparentPoints.h"
#include "dialogs.h"
#include <QList>

class QDoubleSpinBox;
class QSpinBox;
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

private:
  // original values


  QList<bool> origFixedTranparent;
  QList<bool> origPointsOnlyFix;

  QList<Mesh_Info*> meshes;
  // widgets

  QList<QCheckBox*> fixedPointsOnlyBoxes;
  QList<QCheckBox*> fixedTransparentBoxes;


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
