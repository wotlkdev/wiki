# WoTLK Modding Resources

All the pages were moved into [docs](./docs)!!!

## Fork / Move Repo Guide

- Create a fork or push it

- Change [docs/_config.yml](./docs/_config.yml#L3) `remote_theme` to your own repository
- Go to your repository settings under `Settings` -> `Actions` -> `General` -> `Workflow permissions` and enable `Read and write permissions`
- Change [_includes/nav.html](./_includes/nav.html#L61-L64) sections marked `<!-- Selected -->` and `<!-- Not selected -->` from `wow-intro-tutorials-drafts` to whatever your repository is called.
- Set up github pages to use the `gh_pages` branch of this repository (do **not** use `main`, dbc pages are built to the  to the `gh_pages` branch)

## Building locally (Windows)

- Clone repository
- Install [ruby 2.5](https://github.com/oneclick/rubyinstaller2/releases/download/RubyInstaller-2.5.5-1/rubyinstaller-devkit-2.5.5-1-x64.exe)
- Open a new powershell command window and navigate to your repository
- Run the command `gem install bundler` (only needed once)
- Run the command `bundle install` (only needed once)
- Start the local development server with `bundle exec jekyll serve --watch --incremental`

_Note: the navigation bar and links are generally broken on local installations._