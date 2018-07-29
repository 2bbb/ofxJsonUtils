# ofxJsonUtils

utilities for `ofJson`

## API

### ofJson loadFromFile(const std::string &path, bool isInDataDir = true)

* simple load

### ofJson convert(const T &value)
### void parse(const ofJson &json, T &value)

* allowed type
  * ofJson (a.k.a. nlohmann::json)
  * arithmetic type (i.e., int, float, ...)
  * std::string
  * ofVecNf
  * ofRectangle
  * ofColor_<PixelType>
  * class has toJson / loadJson
### ofJson create(std::string key, T &value, [...])

* utility for custom class

### void load(const ofJson &json, const std::string &key, T &value, [...])

* utility for custom class

## Dependencies

### [nlohmann/json](https://github.com/nlohmann/json/)

[v2.1.1](https://github.com/nlohmann/json/releases/tag/v2.1.1)

MIT License.

```
MIT License 

Copyright (c) 2013-2017 Niels Lohmann

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

## Update history

### 2018/07/29 ver 0.1.1 release

* refactor
* add parse / convert about `glm`

### 2017/10/01 ver 0.1.0 release

* big refactor
* add NDJson support
* add of0.10 API
  * ofLoadJson
  * ofSaveJson
  * ofSavePrettyJson
  * ofSerialize
  * ofDeserialize

### 2017/03/05 ver 0.0.3 release

* tiny bugfixes.

### 2016/09/12 ver 0.0.2 release

### 2016/05/23 ver 0.0.1 release

## Special Thanks

* [TOMOTO Yusuke](https://github.com/yusuketomoto) (#1, #2, #3, #5)
* [Naoto HIÉDA](https://github.com/micuat) (#6)
* [nariakiiwatani](https://github.com/nariakiiwatani) (#7, #8, [ofxJsonUtilsUtils](https://github.com/nariakiiwatani/ofxJsonUtilsUtils))
* [yumetodo](https://github.com/yumetodo) (#4)

## License

MIT License.

## Author

* ISHII 2bit
* i[at]2bit.jp

## At the last

Please create a new issue if there is a problem.
And please throw a pull request if you have a cool idea!!

If you get happy with using this addon, and you're rich, please donation for support continuous development.

Bitcoin: `17AbtW73aydfYH3epP8T3UDmmDCcXSGcaf`
