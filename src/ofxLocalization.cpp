/**
 * ofxLocalization
 * simple openFrameworks addon for creating a translation database
 *
 * Copyright (c) 2012 James George
 * Development Supported by YCAM InterLab http://interlab.ycam.jp/en/
 * http://jamesgeorge.org + http://flightphase.com
 * http://github.com/obviousjim + http://github.com/flightphase
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "ofxLocalization.h"

bool ofxLocalization::load(string languageFile){
	//flanguageFile = ofToDataPath(languageFile);
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
	language = ofToLower(language);
	if(language == "" || translation.find(language) == translation.end()){
		ofLogError("ofxLocalization::setCurrentLanguage") << "Couldn't find language " << language;
		return;
	}
	currentLanguage = language;
}

string ofxLocalization::translateKey(string key){
	return translateKeyToLanguage(key, currentLanguage);
}

string ofxLocalization::translateKeyToLanguage(string key, string language){
	language = ofToLower(language);

	if(translation.find(language) == translation.end()){
		ofLogError("ofxLocalization::translateKey") << "Couldn't find language " << language <<  endl;
		return key;	
	}

	if(translation[language].find(key) == translation[language].end()){
		ofLogError("ofxLocalization::translateKey") << "Couldn't find key " << key << " in language " << language <<  endl;
		return key;
	}
	return translation[language][key];
}

string ofxLocalization::keyForTranslation(string word, string language){
	language = ofToLower(language);

	map<string, string>::iterator it = translation[language].begin();
	while(it != translation[language].end()){
		if(it->second == word){
			return it->first;
		}
		it++;
	}
	ofLogError("ofxLocalization::keyForTranslation") << "Couldn't find key for word " << word << " in language " << language;
	return "";
}

string ofxLocalization::keyForTranslation(string word){
	return keyForTranslation(word, currentLanguage);
}
