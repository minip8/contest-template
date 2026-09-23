#!/usr/bin/env python3
# Export the Makefile, template and headers/ to a KACTL-style PDF (landscape, 3 columns).
# The page header lists the sections on that page, so it can be appended to the KACTL notes.
# usage: ./export_pdf.py [-o template.pdf] [-p FIRST_PAGE]
import argparse, re, shutil, subprocess, tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent

PREAMBLE = r"""
\documentclass[10pt,a4paper,landscape]{article}
\usepackage[T1]{fontenc}
\usepackage{lmodern}
\usepackage[margin=0.9cm,top=1.6cm,headsep=0.25cm]{geometry}
\usepackage{multicol,fancyhdr,listings,xcolor,etoolbox}
\setlength{\columnsep}{0.4cm}
\setlength{\columnseprule}{0.2pt}
\setlength{\parindent}{0pt}
\pagestyle{fancy}
\fancyhf{}
% \kactlsec{page}{name} lines in the .aux collect each page's section names for the header
\makeatletter
\newcommand{\kactlsec}[2]{%
  \ifcsundef{kactl@p#1}{\csgdef{kactl@p#1}{#2}}{%
    \ifcsstring{kactl@l#1}{#2}{}{\csgappto{kactl@p#1}{, #2}}}%
  \csgdef{kactl@l#1}{#2}}
\newcommand{\kactlmark}[1]{\protected@write\@auxout{}{\string\kactlsec{\thepage}{#1}}}
\makeatother
\lhead{\textbf{\ifcsdef{kactl@p\thepage}{\csuse{kactl@p\thepage}}{}}}
\rhead{\thepage}
\renewcommand{\headrulewidth}{0.4pt}
\definecolor{cmt}{gray}{0.35}
\lstset{
  basicstyle=\ttfamily\scriptsize,
  keywordstyle=\bfseries,
  commentstyle=\color{cmt}\itshape,
  stringstyle=\ttfamily,
  columns=fullflexible,
  keepspaces=true,
  upquote=true,
  showstringspaces=false,
  breaklines=true,
  breakatwhitespace=false,
  tabsize=4,
  aboveskip=2pt,
  belowskip=6pt,
}
\lstdefinelanguage{kactlmake}{
  morecomment=[l]{\#},
  morekeywords={include},
}
\newcommand{\kactlfile}[3]{%
  \par\kactlmark{#3}\noindent\rule{\linewidth}{0.4pt}\par\nopagebreak
  \noindent\textbf{\small #1}\hfill{\ttfamily\scriptsize #2}\par\nopagebreak
}
\begin{document}
\setcounter{page}{@PAGE@}
\begin{multicols*}{3}
"""

END = r"""
\end{multicols*}
\end{document}
"""

# (path relative to template/, listings language); headers/ is globbed in
FILES = [("Makefile", "kactlmake"), ("template.cpp", "C++")]
HASH_LINE = re.compile(r"^\s*/\*\s*[0-9a-f]{6}\b.*\*/\s*$")


def cpp_hash(text):
    r = subprocess.run(["sh", str(ROOT / "hash.sh")], input=text, text=True, capture_output=True)
    return r.stdout.strip() if r.returncode == 0 else ""


def tex_escape(s):
    return "".join({"\\": r"\textbackslash{}", "_": r"\_", "#": r"\#", "$": r"\$", "%": r"\%",
                    "&": r"\&", "{": r"\{", "}": r"\}", "~": r"\textasciitilde{}",
                    "^": r"\textasciicircum{}"}.get(c, c) for c in s)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("-o", "--output", default=str(ROOT / "template.pdf"))
    ap.add_argument("-p", "--first-page", type=int, default=1, help="number of the first page")
    args = ap.parse_args()

    files = FILES + [(str(p.relative_to(ROOT)), "C++") for p in sorted((ROOT / "headers").glob("*.h"))]

    with tempfile.TemporaryDirectory() as tmp:
        tmp = Path(tmp)
        body = []
        for i, (name, lang) in enumerate(files):
            lines = (ROOT / name).read_text().rstrip("\n").split("\n")
            # drop leading checksum comments; the hash goes in the title bar instead, like KACTL
            while lines and HASH_LINE.match(lines[0]):
                lines.pop(0)
            text = "\n".join(lines) + "\n"
            h = cpp_hash(text) if lang == "C++" else ""
            src = tmp / f"f{i}.txt"
            src.write_text(text)
            sec = tex_escape(Path(name).stem)  # header name: Makefile, template, debug, ...
            body.append(f"\\kactlfile{{{tex_escape(name)}}}{{{h}}}{{{sec}}}\n"
                        f"\\lstinputlisting[language={{{lang}}}]{{{src.name}}}\n"
                        f"\\kactlmark{{{sec}}}\n")  # again at the end, for files spilling onto the next page

        tex = PREAMBLE.replace("@PAGE@", str(args.first_page)) + "".join(body) + END
        (tmp / "doc.tex").write_text(tex)
        for _ in range(2):  # the header reads section names from the previous pass's .aux
            r = subprocess.run(["pdflatex", "-interaction=nonstopmode", "-halt-on-error", "doc.tex"],
                               cwd=tmp, capture_output=True, text=True)
            if r.returncode:
                print(r.stdout[-3000:])
                raise SystemExit("pdflatex failed")
        shutil.copy(tmp / "doc.pdf", args.output)
    print(f"wrote {args.output}")


if __name__ == "__main__":
    main()
