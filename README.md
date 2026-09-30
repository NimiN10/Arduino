# Arduino

A collection of Arduino projects. Each project lives in its own folder with a
sketch and a `README.md` listing its hardware.

## Projects

<!-- projects:start -->
| Project | Status | Sketch |
|---------|--------|--------|
| [Snake](Snake/) | done | [Snake_Game.ino](Snake/Snake_Game.ino) |
| [Water_sensor](Water_sensor/) | wip |  |
<!-- projects:end -->

## Managing projects

```sh
tools/project.sh new Traffic_Light          # scaffold a new project from _template/
tools/project.sh status Traffic_Light done  # update its status (idea, wip, done, ...)
tools/project.sh list                       # show all projects
tools/project.sh index                      # refresh the table above
```

To change what new projects start with, edit the files in `_template/`.
