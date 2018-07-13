// main.qml

import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    id: mainWindow;

    visible: true;

    width: 640; height: 480;

    title: qsTr("Hello World");

    Component
    {
        id: columnComponent

        TableViewColumn { width: 100; }
    }

    TableView {
        id: mainTableView;

        anchors.fill: parent;

        model: xlsxModel;

        resources:
        {
            var roleList = xlsxModel.customRoleNames;
            var temp = [];
            for(var i=0; i<roleList.length; i++)
            {
                var role  = roleList[i];
                temp.push(columnComponent.createObject(mainTableView, { "role": role, "title": role}));
            }
            return temp;
        }

    } // TableView

} // Window
