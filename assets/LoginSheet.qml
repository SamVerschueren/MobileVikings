import bb.cascades 1.0
import bb.system 1.0

import mvvm.viewmodels 1.0

/**
 * This sheet is shown at startup and overlays the application. When the
 * user succesfully logs in, the sheet will be closed.
 */
Sheet {
    id: loginSheet
    peekEnabled: false
    
    Page {
        titleBar: TitleBar {
            title: qsTr("Mobile Vikings")

            acceptAction: ActionItem {
                id: cmdLogin
                title: qsTr("Sign in")
                enabled: false
                onTriggered: login()
            }
        }

        Container {
            layout: DockLayout {}

            ActivityIndicator {
                id: activityIndicator
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Center
                preferredWidth: 200
                preferredHeight: 200
                visible: false
            }

            Container {
                id: mainContainer
                topPadding: 50
                leftPadding: 30
                rightPadding: 30
                layout: StackLayout {
                }

                // Bind this TextField to the username property of the LoginViewModel.
                TextField {
                    id: txtUsername
                    text: loginVM.username
                    hintText: qsTr("Username")
                    inputMode: TextFieldInputMode.EmailAddress
                    bottomMargin: 20
                    onTextChanging: {
                        cmdLogin.enabled = text.trim() != "" && txtPassword.text.trim() != ""
                    }
                }

                // Bind this TextField to the password property of the LoginViewModel.
                TextField {
                    id: txtPassword
                    text: loginVM.password
                    hintText: qsTr("Password")
                    inputMode: TextFieldInputMode.Password
                    onTextChanging: {
                        cmdLogin.enabled = text.trim() != "" && txtUsername.text.trim() != ""
                    }
                    input.onSubmitted: login()
                }
            }
        }
        
        attachedObjects: [
            // Instantiate the LoginViewModel, give it a unique id and bind the properties with the textfields

            LoginViewModel {
                id: loginVM
                username: txtUsername.text
                password: txtPassword.text
                
                onLoginCompleted: {
                   if (result) {
                        // close the sheet if the user is succesfully logged in
                        loginSheet.close();
                    } else {
                        // show the errordialog if the user failed to log in
                        errorDialog.body = message;
                        errorDialog.show();
                        
                        reset();
                    }
                }
            },
            SystemDialog {
                id: errorDialog
                cancelButton.label: undefined
                title: qsTr("Error")
                body: qsTr("An unknown error occured")
            }
        ]
    }
    onOpenedChanged: {
        if(opened) {
            reset(true);
        }
    }
    
    function login() {
        txtPassword.loseFocus();
        
        cmdLogin.enabled = false;
        mainContainer.visible = false;

        activityIndicator.visible = true;
        activityIndicator.start();

        loginVM.login()
    }

    function reset(hardReset) {
        activityIndicator.stop();
        activityIndicator.visible = false;

        cmdLogin.enabled = false;
        mainContainer.visible = true;
        
        if(hardReset) {
            txtUsername.resetText();
            txtPassword.resetText();
            
            txtUsername.requestFocus()
        }
    }
}