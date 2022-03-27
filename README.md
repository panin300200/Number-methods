# Splain
Hello! The project make labaratory number one of number methods by NSTU. Our teacher is Markov S.I.
You can build and run our program on your machine. There is tutorial below.
## How run Splain
### Step 1: git clone
Take it for you convenience:
```
mkdir test
cd test
```
next:
```
git clone "https://github.com/panin300200/Number-methods.git"
```
### Step 2: use cmake
Install cmake.


On windows use this links (guide) :
```
https://aneescraftsmanship.com/how-to-install-and-configure-cmake-in-windows/
```
On macOS:
```
brew install cmake
```
On linux:
```
sudo apt-get install cmake
```
## Step 3: build
```

cd Number-methods
cmake -G "Unix Makefiles"

make
```
## Step 4: you can move it wherever you want
```

mv splain* {comfortable path}

```
## In conclusion:
You can clear temp:
```
cd ../
rm -r test
```

# Documentation
```
splain -help
```
or
```
splain -h
```
You get this message:
```
-h|-help :
        print all documentation.
-f :
        print all function which are using.

-path [path-to-directory]:
        set path to directory where will save tabels.
-a :
         set value of a. It is start of range.
-b :
        set value of b. It is end of range.
-s :
        set amount segments value.
```
## How to know which functions use?
```
splain -f
```
Result depend on how set function when compile it. My result:
```
Table of f(x) = x
Table of f(x) = x^2
Table of f(x) = x^3
Table of f(x) = x^4
Table of f(x) = sin(x)
```
## How interpolation other value of range and amount of segments?
```
splain -a 0 -b 1 -s 10
```
After -a is range start. After -b end range. After -s amount of segments. This values set by default.
## How to save in other folder?
Use flags -p|-path {your path}
```
splain -p ~/Downloads
```


Copyright (C) Komarik Zakhar
