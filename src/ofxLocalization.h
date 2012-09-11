//
//  ofxLocalization.h
//  Duration
//
//  Created by obvioujim ( http://www.jamesgeorge.org ) @ ycam interlab ( http://interlab.ycam.jp )
//
//

#pragma once

#include "ofMain.h"

class ofxLocalization {
  public:
	
	bool load(string languageFile);
	vector<string>& getLanguages();
	vector<string>& getKeys();
	string getCurrentLanguage();
	void setCurrentLanguage(string language);
	string translateKey(string key);
	string translateKeyToLanguage(string key, string language);
	
  protected:
	string currentLanguage;
	vector<string> languages;
	vector<string> keys;
	//maps language to -> (key->translation) map
	//ie: pass in japanese as the translation["japanese"]["hello"] returns "こんにちは"
	map< string, map<string,string> > translation;
};


