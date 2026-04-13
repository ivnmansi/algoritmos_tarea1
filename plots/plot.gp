set datafile separator ","
set terminal pngcairo font "Arial,12" size 1200,720
set xlabel 'n'
set ylabel 'Tiempo promedio (s)'
set grid
set key outside

set style data lines
set key autotitle columnhead

search_file = 'db/search_benchmark.csv'
sort_file   = 'db/sort_benchmark.csv'

search_out = 'plots/search_benchmark.png'
sort_out   = 'plots/sort_benchmark.png'

has_search = int(system(sprintf("test -f '%s' && echo 1 || echo 0", search_file)))
has_sort   = int(system(sprintf("test -f '%s' && echo 1 || echo 0", sort_file)))

if (!has_search) {
	print sprintf("ERROR: no existe %s", search_file)
	exit 1
}
if (!has_sort) {
	print sprintf("ERROR: no existe %s", sort_file)
	exit 1
}

set autoscale
set xtics
set ytics
set key outside

# Search benchmark
set output search_out
set title 'Search benchmark'
nf = int(system(sprintf("awk -F, 'NR==2{print NF; exit}' \"%s\"", search_file)))
if (nf < 2) {
	print sprintf("ERROR: CSV inválido (pocas columnas): %s", search_file)
	exit 1
} else {
	plot for [col=2:nf] search_file using 1:col lw 2 title columnhead(col)
}
unset output

# Sort benchmark
set output sort_out
set title 'Sort benchmark'
nf = int(system(sprintf("awk -F, 'NR==2{print NF; exit}' \"%s\"", sort_file)))
if (nf < 2) {
	print sprintf("ERROR: CSV inválido (pocas columnas): %s", sort_file)
	exit 1
} else {
	plot for [col=2:nf] sort_file using 1:col lw 2 title columnhead(col)
}
unset output