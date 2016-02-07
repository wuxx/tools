set nu
set hlsearch
syntax on

set tabstop=4
set expandtab
set sw=4
set cindent
set smarttab
"set softtabstop=4
"set autoindent

set tags+=./tags
set tags+=./../tags
set tags+=./../../tags
set tags+=./../../../tags
set tags+=./../../../../tags
set tags+=./../../../../../tags

"让vim记忆上次编辑的位置
autocmd BufReadPost *
            \ if line("'\"")>0&&line("'\"")<=line("$") |
            \   exe "normal g'\"" |
            \ endif
"让vim记忆上次编辑的位置
