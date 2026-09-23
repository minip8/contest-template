#!/usr/bin/env python3
# Export the Makefile, template and headers/ to a KACTL-style PDF (landscape, 3 columns).
# usage: ./export_pdf.py [-o template.pdf] [-t "Team Name"]
import argparse, re, shutil, subprocess, tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent

PREAMBLE = r"""
\documentclass[10pt,a4paper,landscape]{article}
\usepackage[T1]{fontenc}
\usepackage{lmodern}
\usepackage[margin=0.9cm,top=1.6cm,headsep=0.25cm]{geometry}
\usepackage{multicol,fancyhdr,listings,xcolor}
\setlength{\columnsep}{0.4cm}
\setlength{\columnseprule}{0.2pt}
\setlength{\parindent}{0pt}
\pagestyle{fancy}
\fancyhf{}
\lhead{\textbf{@TEAM@}}
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
\newcommand{\kactlfile}[2]{%
  \par\noindent\rule{\linewidth}{0.4pt}\par\nopagebreak
  \noindent\textbf{\small #1}\hfill{\ttfamily\scriptsize #2}\par\nopagebreak
}
\begin{document}
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
    ap.add_argument("-t", "--team", default="Team Reference")
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
            body.append(f"\\kactlfile{{{tex_escape(name)}}}{{{h}}}\n"
                        f"\\lstinputlisting[language={{{lang}}}]{{{src.name}}}\n")

        tex = PREAMBLE.replace("@TEAM@", tex_escape(args.team)) + "".join(body) + END
        (tmp / "doc.tex").write_text(tex)
        r = subprocess.run(["pdflatex", "-interaction=nonstopmode", "-halt-on-error", "doc.tex"],
                           cwd=tmp, capture_output=True, text=True)
        if r.returncode:
            print(r.stdout[-3000:])
            raise SystemExit("pdflatex failed")
        shutil.copy(tmp / "doc.pdf", args.output)
    print(f"wrote {args.output}")


if __name__ == "__main__":
    main()
