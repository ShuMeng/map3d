/* PickWindow.h */

#ifndef PICKWINDOW_H
#define PICKWINDOW_H

#include "GenericWindow.h"
#include "MeshList.h"

struct PickInfo;
class FileDialogWidget;
class Mesh_Info;

class PickWindow: public Map3dGLWidget
{
public:
  PickWindow(QWidget* parent); // this one is implicit in its rms-ness (called by Qt with only one arg)
  PickWindow(QWidget* parent, bool rms);
  ~PickWindow();
  static PickWindow* PickWindowCreate(int _width, int _height, int _x, int _y);


  Mesh_List meshes; 

  void initializeGL();
  virtual void paintGL();
  void Destroy();

  virtual void keyPressEvent ( QKeyEvent * event );
  virtual void keyReleaseEvent ( QKeyEvent * event );
  virtual void mouseMoveEvent ( QMouseEvent * event );
  virtual void mousePressEvent ( QMouseEvent * event );
  virtual void mouseReleaseEvent ( QMouseEvent * event );
  virtual void enterEvent( QEvent* event ); 
  virtual void leaveEvent( QEvent* event ); 

  void closeEvent(QCloseEvent *event);
  
  void RMSButtonPress(QMouseEvent* event);
  void RMSButtonRelease(QMouseEvent* event);
  void RMSMotion(QMouseEvent* event);

  int OpenMenu(QPoint point);
  void MenuEvent(int menu_data);

  void DrawNode();
  void DrawPlot(int left, int right); // draws ONLY the plot, from [left to right), covering the entire plot space
  void SetStyle(int x);



  bool MatrixOnlyContainZero(Surf_Data* data,float **matrixvals);


  void SetNearestElec(int x);

 void SetIndividualRange(int x);

  // gets the frame range for specified subseries.  Entire series if subseriesNum < 0
  void getFrameRange(int subseriesNum, int& left, int& right);

  bool rms;
  PickInfo *pick;
  Mesh_Info *mesh;          // mesh that "owns" this pick window
  bool click;

  float axiscolor[4];           //in addition to fg and bg defined in GenericWindow
  float graphcolor[4];
  float leftoffset, rightoffset, bottomoffset, topoffset;
  float graph_width;

  // info for the rms window (inside the FilesDialog) only
  FileDialogWidget* fileWidget;
  int window_line; // when we're dragging, we need to know if it's the line or right marker
};


#endif
