KIL VCS - A local version control system

----------------------------------------------------------------------------------------------------------------------------
The following define the (IMPLEMENTED) recognized commands and their behaviours:

> init RepoName
  Initializes a repository named RepoName.

> add fileName
  Mark file named fileName for tracking.

> commit [-a] "Commit Message"
  Commit changes.
  With '-a' option, commits file creations (of added files), file deletions, and changes to tracked files.
  Without '-a' option, commits only file deletions, and changes to tracked files.

> status
  Output information about which files have been added, deleted or changed on that branch since the last commit.

----------------------------------------------------------------------------------------------------------------------------
The following define the (YET TO BE IMPLEMENTED) recognized commands and their behaviours:

> clone /path/to/repo
  Clones an existing respository.
  
> checkout -b branchName
  Creates a new branch named branchName and switches to it.
> checkout branchName
  Switches to existing branch named branchName.

> branch
  List all branches in the repository.
> branch -d branchName
  Deletes branch named branchName.

> merge branchName
  Merge branchName into your current branch.
  
> diff
  View difference between current state and state at the last commit in that branch.
> diff commitHash1 commitHash2
  View difference between states of two given commits.

> conflicts
  View unresolved merge conflicts.

> resolve
  Marks marge conflicts as resolved.

> log
  View path down tree leading up to last commit, see commit hashes.

> undo [filename / ALL]
  Undo all uncommitted work, and go back to state of last commit.
  filename: operate on the specified file
  ALL:      operate on all files
  [see Note 1]

> reset [-s / -h] <commithash> <branchname>
  Jump to a previous commit.
  -s: keep files in current state:
  -h: reset files to state of the commit


### NOTES ###
1. If trying to operate on a file named ALL, refer to it using its path eg. ./ALL.
