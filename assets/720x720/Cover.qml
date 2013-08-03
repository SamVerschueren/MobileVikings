import bb.cascades 1.0

Container {
    property string title
    property string credits
    property string expiry

    layout: DockLayout {}
    background: Color.create("#ff262626")
    
    Container {
        background: Color.create("#ff121212")
        horizontalAlignment: HorizontalAlignment.Fill
        preferredHeight: 56.0

        Container {
            layoutProperties: StackLayoutProperties {
                spaceQuota: 1.0
            }

            leftPadding: 17.0
            topPadding: 6.0
            
            Label {
                text: title
                verticalAlignment: VerticalAlignment.Center
                textStyle.color: Color.create("#ff00a7de")
            }
        }
        
        Container {
            preferredHeight: 2.0
            background: Color.create("#ff00a7de")
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Bottom
        }
    }
    
    Container {
        verticalAlignment: VerticalAlignment.Center
        horizontalAlignment: HorizontalAlignment.Center

        topPadding: 40.0
        Label {
            text: credits
            textStyle.fontSize: FontSize.XXLarge
            horizontalAlignment: HorizontalAlignment.Fill
            textStyle.textAlign: TextAlign.Center
            textStyle.color: Color.create("#ffd3d3d3")
        }
        
        Label {
            text: expiry
            horizontalAlignment: HorizontalAlignment.Fill
            textStyle.textAlign: TextAlign.Center
            textStyle.color: Color.create("#ffd3d3d3")
        }
    }
    
}