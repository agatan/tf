# C++ complicated type formatter

When you write C++ program, especially use template meta programming techniques,
some types that compiler tell us become very very complicated.

`tf` formats C++ types and outputs it.

# Build
```
git clone https://github.com/agatan/tf.git
cd tf
mkdir build
cd build && cmake ..
make
cp ./src/tf SOME_DIRECTORY_IN_YOUR_PATH
```

# Usage
```
echo "some<very<very, complicated>::type<in>, your>::code" | tf
```
