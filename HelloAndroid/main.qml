// main.qml

import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Window {
    id : mainWindow;
    visible : true;
    title : qsTr("Hello Android");
    /* width: 640; height: 480; */

    Component
    {
        id : columnComponent;
        TableViewColumn {
            resizable : true;
            movable : false;
            /*width: 100;*/
        }
    }

    TableView
    {
        id : mainTableView;
        anchors.fill : parent;
        model : xlsxModel;

        frameVisible : true;
        highlightOnFocus : true;

        horizontalScrollBarPolicy : Qt.ScrollBarAlwaysOn;
        verticalScrollBarPolicy : Qt.ScrollBarAlwaysOn;

        resources:
        {
            var roleList = xlsxModel.customRoleNames;
            var temp = []; // empty object
            for(var ic = 0 ; ic < roleList.length ; ic++ )
            {
                var role  = roleList[ic];
                var colObj = columnComponent.createObject( mainTableView, { "role": role, "title": role } );
                temp.push(colObj);
            }
            return temp;
        }

    } // TableView

} // Window
