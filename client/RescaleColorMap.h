#ifndef RESCALECOLORMAP_H
#define RESCALECOLORMAP_H
#include "ui_RescaleColorMap.h"

#include "dialogs.h"
#include <QList>


class QDoubleSpinBox;



class RescaleColorMap: public QDialog, public Ui::RescaleColorMap
{
     Q_OBJECT;
public:
    RescaleColorMap();
private slots:
    void on_minSpinBox_valueChanged(double arg1);
    void on_maxSpinBox_valueChanged(double arg1);
    void on_ApplyScaleButton_clicked();
    void on_CancleScaleButton_clicked();


private:

    QList<Mesh_Info*> meshes;
};

#endif // RESCALECOLORMAP_H
