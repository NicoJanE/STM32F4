
## 1 GitHUb. Create the (build) the repo.
Make sure the repo is public first
- Settings -> Pages.
-- Branch -> master ->save (= build)


## 2. Use customize architect theme in Preview container
I have a customized theme which is based on the GitHub Architect Theme [see here](https://github.com/pages-themes/architect)

This customized Theme adds a left **content navigation panel** to each page. The navigation items can be added to this page be includes in the MarkDown (MD) file, be means of the **Front Matter** principle. Below is an example of four items that are added to the navigation panel after Jekyll has complied the pages to HTML. 

Add this to the MarkDown files:
```
---
layout: default_c
RefPages:
 - howto_create_A_dev_container
 - howto_create_a_swarm
 - howto_install_other_PHP_versions
 - howto_steps_for_debugging
--- 
```
For sub page a 'home (SubSite)' button will automatically included as last item. **Be aware** that the above pages are expected to be found in the directory: **Howtos** only the index.md file is expected in the root directory
```
 .\root\index.md
 .\root\Howtos\howto_create_A_dev_container.md
```
for this reason don't include the **Howtos** directory in the front matter section. The path to the **Howtos** directory can be **configured** in the \_config.yml file.

## For preview markdown container(already included)
see also: **\\docker\GitHub preview container template\\**.<br><br>
Make sure the following additional files are placed in the directory where the Mount Bind points to (see:***compose_jekyll.cont.yml***) This directory typically contains the *index.md* file and has a sub-directory 'Howtos'. I will refer to this as the: MD-Root
- MD-Root\_layouts\default_c.html	(*1)
- MD-Root\assets\css\style.scss	(*1)

<small>(These files can be found at: **\GitHub\cust_arcithect-theme\\**) </small>

- The \_config file must be updated with a variable that points the the Howtos directory where the sub documents are located add the following to the *_config.yml* file:
`
BaseDir: Howtos
`

- rebuild website in Jekyll docker:
`bundle exec jekyll build --source /srv/jekyll/markdown_files --destination /srv/jekyll/_site --config /srv/jekyll/_config.yml --trace  --watch`

## For a GitHub(remote) project
- Add the following files to the root GitHub folder:<br>
-- GitHub-PrjRoot\_layouts\default_c.html	<br>
-- GitHub-PrjRoot\css\style.scss	
- Add the \_config to the GitHub project root <br>
-- GitHub-PrjRoot\_config.yml
When this file already exists make sure to add the content <br>
-- In the \_config.yml make sure to set the correct title and description(in the top of the file)