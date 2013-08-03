import bb.cascades 1.0
import bb.system 1.0
import mvvm.viewmodels 1.0

Page {
    id: mainPage
    property bool isExpanded: false
    
    titleBar: TitleBar {
        id: titleBar
        kind: TitleBarKind.FreeForm
        kindProperties: FreeFormTitleBarKindProperties {
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                leftPadding: 10
                rightPadding: 10
                Label {
                    text: mainVM.title
                    textStyle {
                        color: Color.White
                    }
                    verticalAlignment: VerticalAlignment.Center
                    layoutProperties: StackLayoutProperties {
                        spaceQuota: 1
                    }
                }
            }
            expandableArea {
                expanded: isExpanded
                
                content: ListView {
                    id: simList
                    dataModel: mainVM.dataModel
                    preferredHeight: mainVM.dataModel.size() > 3 ? 299 : mainVM.dataModel.size()*100 - 1
                    listItemComponents: [
                        ListItemComponent {
                            type: "item"

                            Container {
                                id: rootContainer
                                preferredHeight: 100
                                
                                Container {
                                    layout: StackLayout {
                                        orientation: LayoutOrientation.LeftToRight
                                    }
                                    leftPadding: 50
                                    rightPadding: 20
                                    topPadding: 20
                                    layoutProperties: StackLayoutProperties {
                                        spaceQuota: 1.0
                                    }

                                    Label {
                                        text: ListItemData.alias
                                        textStyle.fontSize: FontSize.Medium
                                        verticalAlignment: VerticalAlignment.Center
                                        layoutProperties: StackLayoutProperties {
                                            spaceQuota: 1.0
                                        }
                                    }
                                    ImageView {
                                        imageSource: "asset:///images/checked.png"
                                        visible: ListItemData.selected
                                        verticalAlignment: VerticalAlignment.Center
                                        preferredHeight: 35
                                        preferredWidth: 35
                                    }
                                }
                                Divider { }
                            }
                        }
                    ]
                    onTriggered: {
                        mainVM.selectMsisdn(indexPath)

                        toggleExpandableArea()
                    }
                }
                onExpandedChanged: {
                    isExpanded = expanded
                }
            }
        }
    }
    Container {
        layout: DockLayout {
        }

        ActivityIndicator {
            id: activityIndicator
            verticalAlignment: VerticalAlignment.Center
            horizontalAlignment: HorizontalAlignment.Center
            preferredWidth: 200
            preferredHeight: 200
            running: true
        }
        
        Container {
            id: simBalanceContainer
            visible: false
            topPadding: 10.0
            leftPadding: 10.0
            rightMargin: 10.0
            bottomMargin: 10.0

            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }

                Label {
                    preferredWidth: 350
                    text: qsTr("Credit") + ":"
                }
                Label {
                    text: simVM.credits
                }
            }

            Container {
                topMargin: 30.0
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
    
                Label {
                    preferredWidth: 350
                    text: qsTr("SMS") + ":"
                }
                Label {
                    text: simVM.sms
                }
            }
            
            Container {
                topMargin: 5.0
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                
                Label {
                    preferredWidth: 350
                    text: qsTr("Data") + ":"
                }
                Label {
                    text: simVM.data
                }
            }

            Container {
                topMargin: 30.0
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }

                Label {
                    preferredWidth: 350
                    text: qsTr("SMS to MV") + ":"
                }
                Label {
                    text: simVM.smsSuperOnNet
                }
            }
            
            Container {
                topMargin: 5.0
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }

                Label {
                    preferredWidth: 350
                    text: qsTr("Call to MV") + ":"
                }
                Label {
                    text: simVM.voiceSuperOnNet
                }
            }

            Container {
                topMargin: 30.0
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }

                Label {
                    preferredWidth: 350
                    text: qsTr("Expiry date") + ":"
                }
                Label {
                    text: Qt.formatDateTime(simVM.validUntil)
                }
            }
        }

        Container {
            id: messageContainer
            visible: false
            verticalAlignment: VerticalAlignment.Center
            horizontalAlignment: HorizontalAlignment.Center
            leftPadding: 20.0
            rightPadding: 20.0

            Label {
                id: messageTitle
                textStyle.fontSize: FontSize.XXLarge
                horizontalAlignment: HorizontalAlignment.Center
            }
            Label {
                id: messageDescription
                multiline: true
                textStyle.textAlign: TextAlign.Center
            }
        }
    }
    function load() {
        simVM.loadSimBalance();
    }
    function reset() {
        simVM.reset();
        
        activityIndicator.visible = true;
        activityIndicator.start();

        simBalanceContainer.visible = false;
        messageContainer.visible = false;
    }
    attachedObjects: [
        SimBalanceViewModel {
            id: simVM
            service: vikingService
            msisdn: mainVM.title
            onLoadCompleted: {
                if(message == "") {
                    simBalanceContainer.visible = true
                }
                else if(message == "NO_AUTH") {
                    signOut();
                }
                else {
                    messageTitle.text = qsTr("Error")
                    messageDescription.text = message

                    messageContainer.visible = true
                }

                activityIndicator.visible = false;
                activityIndicator.stop();
            }
        }
    ]
    
    function toggleExpandableArea() {
        isExpanded = !isExpanded;
    }
}
