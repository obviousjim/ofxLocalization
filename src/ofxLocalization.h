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
	//slow!
	
	string keyForTranslation(string word);
	string keyForTranslation(string word, string language);
  protected:
	string currentLanguage;
	vector<string> languages;
	vector<string> keys;
	//maps language to -> (key->translation) map
	//ie: pass in japanese as the translation["japanese"]["hello"] returns "こんにちは"
	map< string, map<string,string> > translation;
};


