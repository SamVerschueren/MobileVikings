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
                        type: "data"

                        Container {
                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill
                                topPadding: 10.0
                                rightPadding: 10.0
                                leftPadding: 10.0
                                bottomPadding: 10.0

                                layout: StackLayout {
                                    orientation: LayoutOrientation.LeftToRight
                                }

                                ImageView {
                                    imageSource: "asset:///images/" + ListItemData.statusImage
                                    rightMargin: 20.0
                                }

                                Container {
                                    Label {
                                        text: ListItemData.contact == "" ? ListItemData.to : ListItemData.contact
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
                                topMargin: -5.0
                            }
                        }
                    },
                    ListItemComponent {
                        type: "item"

                        Container {
                            id: root

                            Container {
                                preferredHeight: 5
                                background: root.ListItem.active || root.ListItem.selected ? Color.create("#CC00A8DF") : Color.Transparent
                                horizontalAlignment: HorizontalAlignment.Fill
                            }
                            
                            Container {
                                layout: StackLayout {
                                    orientation: LayoutOrientation.LeftToRight
                                }

                                Container {
                                    preferredWidth: 5
                                    background: root.ListItem.active || root.ListItem.selected ? Color.create("#CC00A8DF") : Color.Transparent
                                    verticalAlignment: VerticalAlignment.Fill
                                }

                                Container {
                                    layoutProperties: StackLayoutProperties {
                                        spaceQuota: 1.0
                                    }
                                    
                                    topPadding: 5.0
                                    rightPadding: 5.0
                                    leftPadding: 5.0
                                    bottomPadding: 5.0

                                    layout: StackLayout {
                                        orientation: LayoutOrientation.LeftToRight
                                    }
                                    
                                    ImageView {
                                        imageSource: "asset:///images/" + ListItemData.statusImage
                                        rightMargin: 20.0
                                    }

                                    Container {
                                        Label {
                                            text: ListItemData.contact == "" ? ListItemData.to : ListItemData.contact
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

                                Container {
                                    preferredWidth: 5
                                    background: root.ListItem.active || root.ListItem.selected ? Color.create("#CC00A8DF") : Color.Transparent
                                    verticalAlignment: VerticalAlignment.Fill
                                }

                                contextActions: [
                                    ActionSet {
                                        title: ListItemData.contact == "" ? qsTr("Unknown") : ListItemData.contact
                                        subtitle: ListItemData.to
                                        actions: [
                                            ActionItem {
                                                title: qsTr("Send Text Message")
                                                imageSource: "asset:///images/ic_textmessage.png"
                                                onTriggered: ListItemData.sendText()
                                            },
                                            ActionItem {
                                                title: qsTr("Call")
                                                imageSource: "asset:///images/ic_call.png"
                                                onTriggered: ListItemData.call()
                                            },
                                            ActionItem {
                                                title: ListItemData.contact == "" ? qsTr("Add to Contact") : qsTr("View Contact")
                                                imageSource: ListItemData.contact == "" ? "asset:///images/add_to_contacts.png" : "asset:///images/ic_view_contact.png"
                                                onTriggered: ListItemData.viewOrAddContact()
                                            },
                                            ActionItem {
                                                title: qsTr("Copy Number")
                                                imageSource: "asset:///images/ic_copy.png"
                                                onTriggered: ListItemData.copyNumber()
                                            }
                                        ]
                                    }
                                ]
                            }

                            Container {
                                preferredHeight: 5
                                background: root.ListItem.active || root.ListItem.selected ? Color.create("#CC00A8DF") : Color.Transparent
                                horizontalAlignment: HorizontalAlignment.Fill
                            }

                            Divider {
                                topMargin: -5.0
                            }
                        }
                    }
                ]

                onTriggered: {
                    var data = dataModel.data(indexPath)
                    
                    if(itemType(data, indexPath) == "item") {
                        data.call()
                    }
                }

                function itemType(data, indexPath) {
                    if (indexPath.length == 1) {
                        return "header"
                    } else {
                        if (data.statusImage == "1-out.png") {
                            return "data"
                        } else {
                            return "item"
                        }
                    }
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