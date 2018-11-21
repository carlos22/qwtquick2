import QtQuick 2.0
import QwtQuick2 1.0

Item {
    id: plotForm

    Text {
        id: text
        text: qsTr("Plot form")
    }

    QwtQuick2Plot {
        id: qwtPlot
        anchors.fill: parent

        Component.onCompleted: initQwtPlot()
    }
}
