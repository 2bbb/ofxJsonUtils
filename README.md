# ofxJsonUtils

utilities for `ofJson`

## API

### ofJson loadFromFile(const std::string &path, bool isInDataDir = true)

* simple load

### ofJson convert(const T &value)
### void parse(const ofJson &json, T &value)

* allowed type
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

## Update history

### 2017/03/05 ver 0.0.3 release

* tiny bugfixes.

### 2016/09/12 ver 0.0.2 release

### 2016/05/23 ver 0.0.1 release

## Special Thanks

* [TOMOTO Yusuke](https://github.com/yusuketomoto)
* [yumetodo](https://github.com/yumetodo)

## License

MIT License.

## Author

* ISHII 2bit [bufferRenaiss co., ltd.]
* ishii[at]buffer-renaiss.com

## At the last

Please create a new issue if there is a problem.
And please throw a pull request if you have a cool idea!!
