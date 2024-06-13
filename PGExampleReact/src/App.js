/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 *
 * @format
 * @flow strict-local
 */

import React, { Component } from 'react';
import { 
	NativeModules, NativeEventEmitter, 
	SafeAreaView, StyleSheet, 
	Text, Button, View
} from 'react-native';

/* $FlowFixMe[missing-local-annot] The type annotation(s) required by Flow's
 * LTI update could not be added via codemod */

const { ProgloveModule } = NativeModules;


const  {
	FEEDBACK_ERROR, FEEDBACK_SUCCESS, FEEDBACK_WARNING,
	ORIENTATION_EAST, ORIENTATION_NORTH, ORIENTATION_SOUTH, ORIENTATION_UNSET, ORIENTATION_WEST
} = ProgloveModule.getConstants();


class App extends Component {
	state = {
		last_barcode: "not read ..."
	};
	async componentDidMount() {
		console.log(ProgloveModule);
		const eventEmitter = new NativeEventEmitter(ProgloveModule);
		this.pairEvent = eventEmitter.addListener("pair", (event) => {
			console.log("Scanner:" + event);
		});
		this.barcodeEvent = eventEmitter.addListener("barcode", (event) => {
			this.setState({last_barcode: event.content});
			console.log("barcode", event);
		});
		this.impulseEvent = eventEmitter.addListener("impulse", (event) => {
			console.log(event);
		});
		var is_active = await ProgloveModule.isActive();
		if(is_active == false) {
			ProgloveModule.bindProglove();
		}
	}
	async componentWillUnmount() {
		ProgloveModule.unbindProglove();
		this.pairEvent.remove();
		this.impulseEvent.remove();
		this.barcodeEvent.remove();
	}
	togglePair = async() => {
		var state = await ProgloveModule.isConnected();
		if(state) {
			ProgloveModule.unpair();
		} else {
			ProgloveModule.pair();
		}
	};
	displayTest = async() => {
		await ProgloveModule.display("PG2", [{
				"header": "Storage Unit",
				"content": "R15"
			}, {
				"header": "Destination",
				"content": "A7"
			}
		]);
	};
	feedbackTest = async() => {
		await ProgloveModule.feedback(FEEDBACK_ERROR);
	};
	orientationTest = async() => {
		await ProgloveModule.orientation(ORIENTATION_SOUTH); // IOS
	};
	render() {
		return (<SafeAreaView>
			<View style={styles.safe_view}>
				<Button title="Pair/Unpair" onPress={this.togglePair} style={styles.safe_style}/>
				<Text  style={styles.safe_style}>{this.state.last_barcode}</Text>
				<Button title="Display" onPress={this.displayTest}  style={styles.safe_style}/>
				<Button title="Feedback" onPress={this.feedbackTest}  style={styles.safe_style}/>
				<Button title="Orientation" onPress={this.orientationTest}  style={styles.safe_style}/>
			</View>
		</SafeAreaView>);
	}
};

const styles = StyleSheet.create({
	safe_view: {
		padding: 30,
		flexDirection:'column'
	},
	safe_style: {
		marginHorizontal: 12
	}
});

export default App;
