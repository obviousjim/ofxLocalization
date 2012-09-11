//
//  ofxLocalization.h
//  Duration
//
//  Created by obvioujim ( http://www.jamesgeorge.org ) @ ycam interlab ( http://interlab.ycam.jp )
//
//

#include "ofxLocalization.h"

bool ofxLocalization::load(string languageFile){
	languageFile = ofToDataPath(languageFile);
	if(ofFilePath::getFileExt(languageFile) != "csv"){
		ofLogError("ofxLocalization::load") << "Expecting CSV file extension: " << languageFile;
	}
	ofFile file(languageFile);
	if(!file.exists()){
		ofLogError("ofxLocalization::load") << " file not found: " << languageFile;
		return false;
	}
	ofBuffer csv = ofBuffer(file);
	string header = ofToLower(csv.getNextLine());
	vector<string> headerComponents = ofSplitString(header, ",",true,true);
	if(headerComponents.size() == 0){
		ofLogError("ofxLocalization::load") << "looks like your header is not a comma delimited file" << header;
		return false;
	}
	if(headerComponents[0] != "key"){
		ofLogWarning("ofxLocalization::load") << "expects the first entry to be key: " << header;
	}
	languages.clear();
	for(int i = 1; i < headerComponents.size(); i++){
		string language = headerComponents[i];
		languages.push_back(language);
		translation[language] = map<string,string>();
		ofLogVerbose("ofxLocalization::load") << "found language " << language;
	}
	
	if(languages.size() == 0){
		ofLogError("ofxLocalization::load") << "didn't find any languages in header: " << header;
		return false;
	}
	
	int line = 0;
	while (!csv.isLastLine()) {
		string nextLine = csv.getNextLine();
		vector<string> components = ofSplitString(nextLine, ",",true,true);
		if(components.size() == 0){
			ofLogVerbose("ofxLocalization::load") << " Skipping empty line " << line;
		}
		else {
			string key = components[0];
			if(key != ""){
				ofLogVerbose("ofxLocalization::load") << "building translation entry for " << key;
				keys.push_back(key);
				for(int i = 1; i < components.size(); i++){
					if(components[i] != "" && i-1 < languages.size()){
						translation[languages[i-1]][key] = components[i];
						ofLogVerbose("ofxLocalization::load") << key << "	translates to " << components[i] << " in " << languages[i-1];
					}

				}
			}
		}
		line++;
	}
	
	currentLanguage = languages[0];
	return true;
}

vector<string>& ofxLocalization::getLanguages(){
	return languages;
}

vector<string>& ofxLocalization::getKeys(){
	return keys;
}

string ofxLocalization::getCurrentLanguage(){
	return currentLanguage;
}

void ofxLocalization::setCurrentLanguage(string language){
	if(language == "" || translation.find(language) == translation.end()){
		ofLogError("ofxLocalization::setCurrentLanguage") << "Couldn't find language" << language;
		return;
	}
	currentLanguage = language;
}

string ofxLocalization::translateKey(string key){
	return translateKeyToLanguage(key, currentLanguage);
}

string ofxLocalization::translateKeyToLanguage(string key, string language){
	if(translation[currentLanguage].find(key) == translation[currentLanguage].end()){
		ofLogError("ofxLocalization::translateKey") << "Couldn't find key" << key << " in language " << language << endl;
		return key;
	}
	return translation[currentLanguage][key];
}
