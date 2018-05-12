import QtQuick 2.3
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtWebEngine 1.2

ApplicationWindow {
	id: window;
	visible: true;
	color: 'black';
	title: 'Web Browser Example';
	width: 1280;
	height: 768;

	header: ToolBar {
		id: toolbar;

		RowLayout {
			anchors.fill: parent;
			ToolButton {
				text: '<'
				enabled: webview.canGoBack;
				onClicked: {
					webview.goBack();
				}
			}
			ToolButton {
				text: '>'
				enabled: webview.canGoForward;
				onClicked: {
					webview.goForward();
				}
			}
			TextField {
				id: urlBar;
				text: 'https://github.com/anak10thn/node-qt5'
				selectByMouse: true;
				Layout.fillWidth: true;
				Layout.rightMargin: 20;

				Keys.onReturnPressed: {
					var protocols = [
						'http',
						'https'
					];

					// Check whether URL lacks protocol
					var found = protocols
						.map(function(protocol) {
							return (text.indexOf(protocol + '://') === 0);
						})
						.reduce(function(found, ret) {
							if (found)
								found;

							return ret;
						}, undefined);

					if (!found) {
						webview.url = 'http://' + text;
					} else {
						webview.url = text;
					}

					webview.scale = 0;
				}

				ProgressBar {
					anchors.bottom: parent.bottom;
					anchors.left: parent.left;
					anchors.right: parent.right;
					id: progressBar;
					to: 100;
					value: 0;
					visible: (value < 100);
					bottomPadding: 5;

					Behavior on value {
						NumberAnimation {
							duration: 400;
							easing.type: Easing.OutQuad;
						}
					}
				}
			}
		}
	}

	WebEngineView {
		id: webview;
		anchors.fill: parent;
		url: 'https://www.google.com/'
		opacity: 0;
		scale: 0;

		Behavior on scale {
			NumberAnimation {
				duration: 600;
				easing.type: Easing.InOutQuart;
			}
		}

		onFullScreenRequested: function(request) {

			if (request.toggleOn) {
				toolbar.visible = false;
				window.showFullScreen();
			} else {
				toolbar.visible = true;
				window.showNormal();
			}

			request.accept()
		}

		onUrlChanged: {
			urlBar.text = url;
		}

		onLoadProgressChanged: {
			progressBar.value = loadProgress;

			if (loadProgress > 30)
				webview.scale = 1;
		}

		Component.onCompleted: {
			opacity = 1.0;
			scale = 1.0;
		}
	}
}