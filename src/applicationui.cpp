// Default empty project template
#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>

#include "LoginViewModel.hpp"
#include "MainViewModel.hpp"
#include "SimBalanceViewModel.hpp"
#include "UsageListViewModel.hpp"
#include "TopupHistoryListViewModel.hpp"
#include "PointsViewModel.hpp"
#include "VikingService.hpp"

using namespace bb::cascades;

ApplicationUI::ApplicationUI(bb::cascades::Application *app) : QObject(app)
{
    // Register the viewmodel so that the QML page can instantiate the viewmodel.
    qmlRegisterType<LoginViewModel>("mvvm.viewmodels", 1, 0, "LoginViewModel");
    qmlRegisterType<MainViewModel>("mvvm.viewmodels", 1, 0, "MainViewModel");
    qmlRegisterType<SimBalanceViewModel>("mvvm.viewmodels", 1, 0, "SimBalanceViewModel");
    qmlRegisterType<UsageListViewModel>("mvvm.viewmodels", 1, 0, "UsageListViewModel");
    qmlRegisterType<TopupHistoryListViewModel>("mvvm.viewmodels", 1, 0, "TopupHistoryListViewModel");
    qmlRegisterType<PointsViewModel>("mvvm.viewmodels", 1, 0, "PointsViewModel");

    qmlRegisterType<VikingService>("bb.vikings.service", 1, 0, "VikingService");

    qRegisterMetaType<GroupDataModel*>("GroupDataModel*");

    // create scene document from main.qml asset
    // set parent to created document to ensure it exists for the whole application lifetime
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);

    // create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();
    // set created root object as a scene
    app->setScene(root);
}

