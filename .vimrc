"For use with gVim on windows, fixes not being able to backspace
:set backspace=indent,eol,start

:set nocompatible

"vim in windows not working with filetypes properly
filetype plugin on

"default single line comment maps
nnoremap // I//<esc>
nnoremap d// I<esc>xx

"default block comment maps
"nnoremap b/ I/**<enter><space>*<enter>*/<enter><esc>kkA<space>
"nnoremap db/ 3dd

"default end (loop/if/case/...) comment (make functions at some point)
if has("win32") || has("win16") || has("win64")
  nnoremap ec A<space>//end<space><esc>pjddk
else
  nnoremap ec A<space>//end<space><esc>p
endif
nnoremap dec I<esc>llld$x

"header comment for group of functions
nnoremap hc O//--------------------------------------------------<enter>
           \//<enter>
           \//--------------------------------------------------<esc>kA

"copy current line without new line
nnoremap cl I<esc>v$hy<esc>

"custom command to source project files
command! -nargs=1 -complete=file OProj source <args>

"Colors
:set t_Co=256
colorscheme jellybeans
:set background=dark

"Vertical bar at column 79 unless file type is a .txt
:set colorcolumn=79
:highlight ColorColumn ctermbg=4

"Pathogen - manage plugins
"call pathogen#infect()

"De-clutter
:set nobackup
:set noswapfile

"Smart filetypes and syntax
:filetype plugin indent on

"ArtisticStyle for C++
"autocmd! BufNewFile,BufRead *.cpp set filetype=cpp
"autocmd FileType cpp :set formatprg=astyle\ -A3pxd
"autocmd FileType cpp noremap <C-f> :!astyle -A3pxd %<CR>

"allowing syntax hilighting of arduino files
autocmd! BufNewFile,BufRead *.ino setlocal ft=arduino
"custom made project files are actualy just vimscript
autocmd! BufNewFIle,BufRead *.cprj setlocal ft=vim

"Syntax highlighting
:syntax on

"Tabs, indents, etc
:set tabstop=2
:set shiftwidth=2
:set expandtab
:set autoindent
:set smarttab
:set hlsearch
:set incsearch

"Line numbers
:set number
:set numberwidth=4

"Code folding
:set foldenable
:set foldmethod=indent

"Spellcheck
":set spell
":set spelllang=en
"regex
":set magic
"Latex
"REQUIRED. This makes vim invoke Latex-Suite when you open a tex file.
"IMPORTANT: grep will sometimes skip displaying the file name if you
"search in a singe file. This will confuse Latex-Suite. Set your grep
"program to always generate a file-name.
":set grepprg=grep\ -nH\ $*
" " The following changes the default filetype back to 'tex':
":let g:tex_flavor='latex'
":let g:Tex_ViewRule_pdf='Preview'
":let g:Tex_CompileRule_pdf = 'xelatex --interaction=nonstopmode $*'
":let g:Tex_MultipleCompileFormats = 'pdf'
"":conf q
":let g:Tex_DefaultTargetPlatform = 'pdf'
"Display symbols in TeX files
":set cole=2
