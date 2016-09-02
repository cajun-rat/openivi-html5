# HTML5 environment for OpenIVI Mobility

This provides a HTML5 runtime for OpenIVI Mobility applications. Documentation is at https://openivimobility.github.io/developing/setting-up-an-html5-development-environment.html[the main OpenIVI docs site].

## Contributing

### Style

Use the google style:
http://google-styleguide.googlecode.com/svn/trunk/cppguide.html

Reformat code using the following before checkin:

    clang-format -style google -i *.cc *.h

### Linting

To use `clang-check` to lint the source tree:

    clang-check -analyze -p build *.cc
