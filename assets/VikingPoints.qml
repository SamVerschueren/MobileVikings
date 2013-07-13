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
            id: vikingPointsContainer
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
                    text: qsTr("Total") + ":"
                }
                Label {
                    text: pointsVM.earnedPoints
                }
            }

            Container {
                topMargin: 30.0
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }

                Label {
                    preferredWidth: 350
                    text: qsTr("Used") + ":"
                }
                Label {
                    text: pointsVM.usedPoints
                }
            }

            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }

                Label {
                    preferredWidth: 350
                    text: qsTr("Unused") + ":"
                }
                Label {
                    text: pointsVM.unusedPoints
                }
            }

            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }

                Label {
                    preferredWidth: 350
                    text: qsTr("Waiting") + ":"
                }
                Label {
                    text: pointsVM.waitingPoints
                }
            }

            Container {
                topMargin: 30.0
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }

                Label {
                    preferredWidth: 350
                    text: qsTr("Top ups") + ":"
                }
                Label {
                    text: pointsVM.usedTopups
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
        pointsVM.loadVikingPoints();
    }
    function reset() {
        pointsVM.reset();
        
        activityIndicator.visible = true;
        activityIndicator.start();

        vikingPointsContainer.visible = false;
        messageContainer.visible = false;
    }
    attachedObjects: [
        PointsViewModel {
            id: pointsVM
            service: vikingService
            onLoadCompleted: {
                if (message == "") {
                    vikingPointsContainer.visible = true;
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