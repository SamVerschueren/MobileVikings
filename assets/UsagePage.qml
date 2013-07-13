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
            id: usageContainer
            visible: false

            ListView {
                dataModel: usageListVM.dataModel
                layout: StackListLayout {
                    headerMode: ListHeaderMode.Sticky
                }

                listItemComponents: [
                    ListItemComponent {
                        type: "header"

                        Header {
                            title: Qt.formatDate(ListItemData)
                        }
                    },
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

                                ImageView {
                                    imageSource: "asset:///images/" + ListItemData.statusImage
                                    rightMargin: 20.0
                                }
                                
                                Container {
                                    Label {
                                        text: ListItemData.to
                                    }

                                    Label {
                                        preferredWidth: 300.0
                                        text: Qt.formatDateTime(ListItemData.start)
                                        textStyle.fontSize: FontSize.XSmall
                                        textStyle.color: Color.Gray
                                        textStyle.fontWeight: FontWeight.W100
                                    }
                                }

                                Label {
                                    text: ListItemData.duration
                                    textStyle.fontSize: FontSize.XSmall
                                    textStyle.color: Color.Gray
                                    textStyle.fontWeight: FontWeight.W100
                                    verticalAlignment: VerticalAlignment.Bottom
                                }

                                Label {
                                    text: ListItemData.price
                                    layoutProperties: StackLayoutProperties {
                                        spaceQuota: 1.0
                                    }
                                    textStyle.textAlign: TextAlign.Right
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
            }
        }
    }
    function load() {
        usageListVM.loadUsage();
    }
    function reset() {
        usageListVM.reset();
        
        activityIndicator.visible = true;
        activityIndicator.start();

        usageContainer.visible = false;
        messageContainer.visible = false;
    }
    attachedObjects: [
        UsageListViewModel {
            id: usageListVM
            service: vikingService
            onLoadCompleted: {
                if (message == "") {
                    if (usageListVM.dataModel.size() == 0) {
                        messageTitle.text = qsTr("No usage data")
                        messageDescription.text = qsTr("There is no usage data available.")

                        messageContainer.visible = true
                    } else {
                        usageContainer.visible = true;
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