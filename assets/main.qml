import bb.cascades 1.0
import mvvm.viewmodels 1.0
import bb.vikings.service 1.0

TabbedPane {
    property bool signedIn: false;
    
    id: rootTabbedPane
    showTabsOnActionBar: true
    Menu.definition: MenuDefinition {
        actions: [
            ActionItem {
                title: qsTr("Sign out")
                imageSource: "asset:///images/bb_action_logout.png"

                onTriggered: signOut()
            }
        ]
    }

    Tab {
        id: simBalanceTab
        title: qsTr("Sim balance")
        imageSource: "asset:///images/bb_icon_sim.png"

        SimBalance {
            id: simBalancePage
        }
    }

    Tab {
        id: usageTab
        title: qsTr("Usage")
        imageSource: "asset:///images/bb_icon_usage.png"

        unreadContentCount: 1
        UsagePage {
            id: usagePage
        }
    }

    Tab {
        id: topUpHistoryTab
        title: qsTr("Top up history")
        imageSource: "asset:///images/bb_icon_topup.png"

        TopUpHistory {
            id: topUpHistoryPage
        }
    }

    Tab {
        id: pointsTab
        title: qsTr("Vikingpoints")
        imageSource: "asset:///images/bb_icon_points.png"

        VikingPoints {
            id: vikingPointsPage
        }
    }

    onCreationCompleted: {
        if (!mainVM.credentials) {
            loginSheet.open()
        }
        else {
            loadPages()
        }
    }

    attachedObjects: [
        MainViewModel {
            id: mainVM
            service: vikingService
            onMsisdnCompleted: {
                for(var i=0; i<list.length; i++) {
                    settingsSheet.addOption(list[i].alias)
                }
            }
            onMsisdnChanged: {
                simBalancePage.reset();
                usagePage.reset();
                topUpHistoryPage.reset();
                vikingPointsPage.reset();

                loadPages()
            }
            onSignOutCompleted: {
                // When the user signed out, this event will be called and the loginsheet can be shown
                loginSheet.open();
            }
        },
        VikingService {
            id: vikingService
        },
        LoginSheet {
            id: loginSheet
            onClosed: {
                loadPages()
            }
        }
    ]

    function signOut() {
        if(signedIn) {
            signedIn = false;
            
            mainVM.signOut()

            simBalancePage.reset();
            usagePage.reset();
            topUpHistoryPage.reset();
            vikingPointsPage.reset();

            rootTabbedPane.activeTab = simBalanceTab
        }
    }

    function loadPages() {
        signedIn = true;

        mainVM.loadMsisdn()

        simBalancePage.load()
        topUpHistoryPage.load()
        vikingPointsPage.load()
        usagePage.load();
    }
}
