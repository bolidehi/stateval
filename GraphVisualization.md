# Introduction #

If you've written a nice smxml statemachine description it's possible to display it as SVG graphic.


# Details #

Run in doc/graph\_gen the script generate\_svg.sh with smxml input file and see output generated in generated folder. You need graphviz/dot installed for this. The DotML transformator is included in the source.

See here output of mobile example:

![http://stateval.googlecode.com/svn/wiki/images/mobile_smxml.png](http://stateval.googlecode.com/svn/wiki/images/mobile_smxml.png)

Currently it just displays all states and transitions. There's no difference between state types (CompoundState, HistoryState, DicisionState,...).