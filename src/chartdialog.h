// This file is part of Agros2D.
//
// Agros2D is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Agros2D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Agros2D.  If not, see <http://www.gnu.org/licenses/>.
//
// hp-FEM group (http://hpfem.org/)
// University of Nevada, Reno (UNR) and University of West Bohemia, Pilsen
// Email: agros2d@googlegroups.com, home page: http://hpfem.org/agros2d/

#ifndef CHARTDIALOG_H
#define CHARTDIALOG_H

#include "util.h"
#include "hermes2d/plugin_interface.h"

class Chart;
class LineEditDouble;
class ValueLineEdit;
class LocalValue;
class FieldInfo;
class SceneViewPost2D;

namespace Module
{
    struct LocalVariable;
}

// definition of chart line
struct ChartLine
{
    Point start;
    Point end;
    double angle;
    int numberOfPoints;
    bool reverse;

    ChartLine() : start(Point()), end(end), angle(0.0), numberOfPoints(0), reverse(false) {}

    ChartLine(Point start, Point end, double angle = 0.0, int numberOfPoints = 200, bool reverse = false)
    {
        this->start = start;
        this->end = end;
        this->angle = angle;
        this->numberOfPoints = numberOfPoints;
        this->reverse = reverse;
    }

    QList<Point> getPoints();
};

class ChartDialog : public QDialog
{
    Q_OBJECT

signals:
    void setChartLine(const ChartLine &chartLine);

public slots:
    void doPlot();

public:
    ChartDialog(SceneViewPost2D *sceneView, FieldInfo *fieldInfo, QWidget *parent = 0);
    ~ChartDialog();

    void showDialog();

protected:
    void hideEvent(QHideEvent *event);

private:
    FieldInfo *m_fieldInfo;
    SceneViewPost2D *m_sceneViewPost2D;

    QTabWidget* tabOutput;
    QTabWidget* tabAnalysisType;

    // geometry
    QComboBox *cmbTimeStep;

    QLabel *lblStartX;
    QLabel *lblStartY;
    QLabel *lblEndX;
    QLabel *lblEndY;

    ValueLineEdit *txtStartX;
    ValueLineEdit *txtStartY;
    ValueLineEdit *txtEndX;
    ValueLineEdit *txtEndY;
    ValueLineEdit *txtAngle;

    QRadioButton *radAxisLength;
    QRadioButton *radAxisX;
    QRadioButton *radAxisY;

    QSpinBox *txtAxisPoints;
    QCheckBox *chkAxisPointsReverse;

    // time
    QLabel *lblPointX;
    QLabel *lblPointY;
    ValueLineEdit *txtPointX;
    ValueLineEdit *txtPointY;

    QComboBox *cmbFieldVariable;
    QComboBox *cmbFieldVariableComp;

    QWidget *widGeometry;
    QWidget *widTime;

    Chart *chart;
    QTableWidget *trvTable;

    void createControls();

    QList<double> getHorizontalAxisValues(ChartLine *chartLine);

    void plotGeometry();
    void plotTime();

    void addTableRow(LocalValue *localValue);

    QStringList headers();
    void addValue(LocalValue *localPointValue, double time, double *yval, int i, int N,
                  PhysicFieldVariableComp physicFieldVariableComp,
                  Module::LocalVariable *physicFieldVariable);

private slots:
    void doFieldVariable(int index);
    void doFieldVariableComp(int index);
    void doSaveImage();
    void doExportData();

    void doChartLine();
    void doTimeStepChanged(int index);
};

#endif // CHARTDIALOG_H
