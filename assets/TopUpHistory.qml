import bb.cascades 1.0
import mvvm.viewmodels 1.0

Page {
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
            id: topupHistoryContainer
            visible: false
    
            ListView {
                dataModel: topupVM.dataModel

                listItemComponents: [
                    ListItemComponent {
                        type: "item"

                        Container {
                            id: mainContainer

                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill
                                topPadding: 10.0
                                rightPadding: 10.0
                                leftPadding: 10.0

                                layout: StackLayout {
                                    orientation: LayoutOrientation.LeftToRight
                                }
                                
                                Container {
                                    Label {
                                        text: Qt.formatDateTime(ListItemData.executedOn)
                                    }

                                    Label {
                                        text: ListItemData.status
                                        textStyle.fontSize: FontSize.XSmall
                                        textStyle.color: Color.Gray
                                        textStyle.fontWeight: FontWeight.W100
                                    }
                                }

                                Container {
                                    verticalAlignment: VerticalAlignment.Center
                                    layoutProperties: StackLayoutProperties {
                                        spaceQuota: 1.0
                                    }
                                    
                                    Label {
                                        text: ListItemData.amount
                                        textStyle.fontSize: FontSize.XXLarge
                                        horizontalAlignment: HorizontalAlignment.Fill
                                        textStyle.textAlign: TextAlign.Right
                                    }
                                }
                            }
                            Divider {
                                
                            }
                        }
                    }
                ]
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
                horizontalAlignment: HorizontalAlignment.Fill
            }
        }
    }
    function load() {
        topupVM.loadTopupHistory();
    }
    function reset() {
        topupVM.reset();
        
        activityIndicator.visible = true;
        activityIndicator.start();

        topupHistoryContainer.visible = false;
        messageContainer.visible = false;
    }
    attachedObjects: [
        TopupHistoryListViewModel {
            id: topupVM
            service: vikingService
            onLoadCompleted: {
                if (message == "") {
                    if(topupVM.dataModel.size() == 0) {
                        messageTitle.text = qsTr("No top up history")
                        messageDescription.text = qsTr("There is no top up history avaialable.")

                        messageContainer.visible = true
                    }
                    else {
                        topupHistoryContainer.visible = true;
                    }
                } else if (message == "NO_AUTH") {
                    signOut();
                } else {
                    messageTitle.text = qsTr("Error")
                    messageDescription.text = message

                    messageContainer.visible = true
                }

                activityIndicator.visible = false;
                activityIndicator.stop();                
            }
        }
    ]
}