// Default empty project template
import bb.cascades 1.0

Page {
    titleBar: TitleBar {
        appearance: TitleBarAppearance.Default
        title: "Tweets"
        branded: TriBool.False
    }
    Container {    // container that includes background + content
        layout: DockLayout {}
        
        ImageView {    // background
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Fill
            imageSource: "asset:///images/background.png"
        }
        
        Container {    // content container
            layout: StackLayout {}
            leftPadding: 20.0
            rightPadding: 20.0
            bottomPadding: 20.0
            topPadding: 20.0

            Container {    // search bar
                topPadding: 10.0
                bottomPadding: 30.0
                
                layout: StackLayout {orientation: LayoutOrientation.LeftToRight}
                TextField {
                    id: searchBar
                    objectName: "searchBar"
                    horizontalAlignment: HorizontalAlignment.Left
                    verticalAlignment: VerticalAlignment.Center
                    hintText: "#bieber"
                    clearButtonVisible: true 
                    inputMode: TextFieldInputMode.Text
                }

	            ImageButton {
	                id: searchButton
	                objectName: "searchButton"
	                defaultImageSource: "asset:///images/search_button.png"
	                preferredHeight: 75
	                preferredWidth: 75
	                horizontalAlignment: HorizontalAlignment.Right
	                verticalAlignment: VerticalAlignment.Center
	                translationY: 2.5
	            
	                onClicked: {
	                    app.startSearch(searchBar.text)
	                }
	            }
            }    // search bar

            ListView {    // ListView of tweetes
                objectName: "listOfTweets"
            }
        }    // content container
		ActivityIndicator {
	        objectName: "spinner"
	        verticalAlignment: VerticalAlignment.Center
	        horizontalAlignment: HorizontalAlignment.Center
	        preferredWidth: 200    
	        preferredHeight: 200   
	    }
    }    // container that includes background + content
}    // page