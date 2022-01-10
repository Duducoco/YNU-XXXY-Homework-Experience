\NeedsTeXFormat{LaTeX2e}[1995/12/01]
\ProvidesClass{imutthesis}
              [2017/09/16 v2.6 PoTong made LaTeX Template for IMUTthesis] 
              
\LoadClass[UTF8,a4paper,zihao=-4]{ctexart}

%%%%%%%加载宏包%%%%%%%%%%%
\RequirePackage[a4paper,left=3cm,right=2.5cm,top=3cm,bottom=2.5cm]{geometry}
\RequirePackage[dvipsnames, svgnames, x11names]{xcolor}
\makeatletter
\let\c@lofdepth\relax
\let\c@lotdepth\relax
\makeatother
\RequirePackage{subfigure}
\RequirePackage{graphicx}
\RequirePackage{float}
\RequirePackage{amsmath}
\RequirePackage{amsfonts}
\RequirePackage{amssymb}
\RequirePackage{bm}
\RequirePackage{fancyhdr}
\RequirePackage{abstract}
\RequirePackage{amsmath}
\RequirePackage[titles,subfigure]{tocloft}    %%不这样会与 subfigure 宏包冲突
\RequirePackage[colorlinks,linkcolor=black]{hyperref}
\RequirePackage{titletoc}
\RequirePackage{listings}
\RequirePackage[toc]{appendix}
\RequirePackage{titlesec}
\RequirePackage{longtable}
\RequirePackage{caption}
\RequirePackage{booktabs}
\RequirePackage{tabularx}
\RequirePackage[version=4]{mhchem}%第四代化学公式宏包

\setcounter{tocdepth}{3}  %目录级数
\linespread{1.5}                   %设置全文1.5倍行间距和word22磅相同

%%%%%%定制章节标题%%%%%%%%%
\ctexset{
	section={
		name = {第,章},
		number = \chinese{section},% \Roman 大小写罗马数字 \arabic 罗马数字
		format = \heiti\zihao{-2}\bfseries\centering    %\raggedleft   \raggedright 左右对齐
	},
	subsection={
		format = \heiti\zihao{-3}\bfseries%\raggedleft
	},
	subsubsection={
		format = \heiti\zihao{4}\bfseries %\raggedleft
	},
	appendix = {
		name = {附录},
		number=\rmfamily\Alph{section},
	},
    paragraph={
    	format = \heiti\zihao{-4}\bfseries %\raggedleft
    }
}

%%%%%定制图目录%%%%%%%%
\CTEXoptions[listfigurename={\centerline {插\hspace{0.25cm} 图}}]
\titlecontents{figure}
[1.7cm]
{}
{\makebox[0pt][r]{%
		\makebox[1.5cm][l]{图\thecontentslabel}%
	}%
}
{\hspace{-1.7cm}}
{\titlerule*[10pt]{.}\contentspage}

%%%%%定制图目录%%%%%%%%
\CTEXoptions[listtablename={\centerline{ 表\hspace{0.25cm} 格}}] 
\titlecontents{table}
[1.7cm]
{}
{\makebox[0pt][r]{%
		\makebox[1.5cm][l]{表\thecontentslabel}%
	}%
}
{\hspace{-1.7cm}}
{\titlerule*[10pt]{.}\contentspage}

%%%%设置章自动另起一页%%%
\let\mysection\section
\def\section{\clearpage\mysection}


%%%%定制页眉页脚%%%%%
\pagestyle{fancy}     
\lhead{}                                                 %左边页眉内容
                                                         %中间页眉内容在导言区设置
\rhead{}                                                 %右边页眉

\lfoot{}                                                 %左边页脚
\cfoot{\thepage}                                         %中间页脚
\rfoot{}                                                 %右边页脚


\renewcommand{\cftsecleader}{\cftdotfill{\cftdotsep}}  %目录一级标题加引导点
\renewcommand{\contentsname}{\centerline{目\hspace{0.25cm} 录}}  %目录
\newcommand{\cnabstractname}{摘 \hspace{0.25cm}要}               %中文摘要
\newcommand{\enabstractname}{Abstract}                           %Abstract
\newcommand{\introductionname}{引 \hspace{0.25cm}言}             %引言
\newcommand{\acknowledgmentname}{致 \hspace{0.25cm}谢}             %谢辞

%%%%%定义中文摘要环境%%%%%
\newenvironment{cnabstract}{%
	\par\small
	\noindent\mbox{}\hfill{\bfseries\heiti \zihao{-2}\cnabstractname}\zihao{-4}\hfill\mbox{}\par
	\vskip 2.5ex}{\clearpage\par\vskip 2.5ex}

%%%%%定义英文摘要环境%%%%%
\newenvironment{enabstract}{%
	\par\small
	\noindent\mbox{}\hfill{\bfseries\heiti \zihao{-2}\enabstractname}\zihao{-4}\hfill\mbox{}\par
	\vskip 2.5ex}{\zihao{-4}\clearpage\par\vskip 2.5ex}

%%%%%定义引言环境%%%%%
\newenvironment{introduction}{%
	\newpage \par\small
	\noindent\mbox{}\hfill{\bfseries\heiti \zihao{-2}  \introductionname}\zihao{-4}\hfill\mbox{}\par
	\vskip 2.5ex}{\zihao{-4}\clearpage\par\vskip 2.5ex}

%%%%定义致谢环境%%%%%%%
\newenvironment{acknowledgment}{%
    \newpage\addcontentsline{toc}{section}{致谢} 
    	\par\small
	\noindent\mbox{}\hfill{\bfseries\heiti \zihao{-2}  \acknowledgmentname}\zihao{-4}\hfill\mbox{}\par
	\vskip 2.5ex}{\newpage\par\vskip 2.5ex}

%%%%%%图表公式编号定制%%%%
\renewcommand {\thetable} {\thesection{}-\arabic{table}}
\renewcommand {\thefigure} {\thesection{}-\arabic{figure}}
\renewcommand {\theequation} {\thesection{}-\arabic{equation}}  %需要“图1-1”改为“图1.1”     可以将指令中的“-”改为“.”
\makeatletter
\@addtoreset{table}{section}
\makeatother
\makeatletter
\@addtoreset{figure}{section}
\makeatother
\makeatletter
\@addtoreset{equation}{section}
\makeatother
\captionsetup[table]{labelsep=space} % 表  space去掉点，period加点，不加space、period就是冒号
\captionsetup[figure]{labelsep=space} % 图  

%%%%%%%定义代码环境%%%%%%%%
\definecolor{dkgreen}{rgb}{0,0.6,0}
\definecolor{gray}{rgb}{0.5,0.5,0.5}
\definecolor{mauve}{rgb}{0.58,0,0.82}

\lstset{
	frame=tb,
	aboveskip=3mm,
	belowskip=3mm,
	showstringspaces=false,
	columns=flexible,
	framerule=1pt,
	rulecolor=\color{gray!35},
	backgroundcolor=\color{gray!5},
	basicstyle={\small\ttfamily},
    %numbers=none,  
    numbers=left,  
    numberstyle=\footnotesize\color{black},
	keywordstyle=\color{blue},
	commentstyle=\color{dkgreen},
	stringstyle=\color{mauve},
	breaklines=true,
	breakatwhitespace=true,
	tabsize=3,
}
\renewcommand{\appendix}{
\setcounter{equation}{0}
\setcounter{table}{0}
\setcounter{figure}{0}
\setcounter{section}{0}
\renewcommand {\thefigure}{\thesection\arabic{figure}}
\renewcommand {\theequation}{\thesection\arabic{equation}}
\renewcommand {\thetable} {\thesection{}\arabic{table}}

\renewcommand\thesection{\Alph{section}}
\ctexset{
	section={
		name = {附录},
		number = \Alph{section},% \Roman 大小写罗马数字 \arabic 罗马数字
		format = \heiti\zihao{-2}\bfseries\centering    %\raggedleft   \raggedright 左右对齐
	},
	subsection={
		number = \Alph{section}.\arabic{subsection},
		format = \heiti\zihao{-3}\bfseries%\raggedleft
	},
	subsubsection={
		format = \heiti\zihao{-4}\bfseries %\raggedleft
	}
}
}
\DeclareCaptionFont{song}{\songti}
\DeclareCaptionFont{minusfour}{\zihao{-4}}
\captionsetup[figure]{%
	format=hang,   
	labelsep=quad, 
	font={song,minusfour,bf}, 
	position=bottom 
}
\captionsetup[table]{%
	format=hang,   
	labelsep=quad, 
	font={song,minusfour,bf}, 
	position=top 
}
\endinput