# Introduction #
There're some specific state types in stateval. Syntax on this page is smxml.

# SimpleState #
This state is used for all states which do not reference a view or include other states. So it's used also for initial and finish states at the moment.

# CompoundState #
Could be parent of other states to group them together. This helps to create logical state groups.

# ViewState #
Must reference a view. The definition of a view is defined by a specific viewmanager plugin. In most cases a view is a graphical screen which contains drawing elements and widgets. But for sure a view could contain what ever you like.

# DecisionState #
Choose at runtime based on variable value which state transition should be walked to.

# HistoryState #
A default transition points to the initial defined state transition. Depending on runtime transitions the target of this transition is redirected to last active state on the same hierarchy level. But pay attention as this is no deep history! A DeepHistoryState has to be implemented in future.