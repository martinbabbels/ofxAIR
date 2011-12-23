﻿package  of.addons.ofxAIR {		import flash.utils.*;	import flash.system.*;	import flash.events.*;	import flash.desktop.*;	import flash.filesystem.*;		import com.adobe.serialization.json.*;		public class ofxAIR extends EventDispatcher {				// Singleton		private static var _instance:ofxAIR;				// Native process		private var _process:NativeProcess;		private var _info:NativeProcessStartupInfo		private var _appPath:String = "/../bin/ofxAIRDebug.app/Contents/MacOS/ofxAIRDebug";				public function ofxAIR() {			NativeApplication.nativeApplication.addEventListener(Event.EXITING, closeConnection);		}				private function connect():void {			var file:File = new File( File.applicationDirectory.nativePath + _appPath);						_info = new NativeProcessStartupInfo();			_info.executable = file;			_process = new NativeProcess();						if(!NativeProcess.isSupported) {				trace("NativeProcess not supported. Make sure you use <supportedProfiles>extendedDesktop</supportedProfiles> in your discriptor file.");				return;			}						_process.addEventListener(ProgressEvent.STANDARD_OUTPUT_DATA, onData);			_process.start(_info);		}				private function onData(e:ProgressEvent):void {			var json:String = _process.standardOutput.readUTFBytes(_process.standardOutput.bytesAvailable);			var json_obj:Object;						try {				json_obj = JSON.decode(json, false);				dispatchEvent(new ofxAIREvent(ofxAIREvent.RECEIVED, json_obj));			} catch(e) {							}		}				private function closeConnection(e:*=null):void {			if(_process.running) {				_process.exit(true);			}		}				public static function write(out:*):void {			instance._process.standardInput.writeUTFBytes(out+"\n");		}				public static function start(appPath:String, appName:String):void {			instance._appPath = appPath+appName+"/Contents/MacOS/"+appName.substring(0,appName.indexOf("."));			instance.connect();		}				public static function addEventListener(type:String, listener:Function):void {			instance.addEventListener(type, listener);		}				public static function get instance():ofxAIR {			if(!_instance) {				_instance = new ofxAIR();			}			return _instance;		}	}	}