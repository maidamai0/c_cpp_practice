import pandas
from plotnine import ggplot, geom_line, aes
from plotnine.facets.facet_wrap import facet_wrap
from plotnine.labels import labs

raw_data = pandas.json_normalize(pandas.read_json("memory_usage.json")["data"])

data_frame = pandas.DataFrame(raw_data)
p = ggplot(data_frame, aes(x='x', y='address', color="legend")) + \
    geom_line() + facet_wrap('legend') + \
    labs(title="Iterate address of matrix", x="iterate index", y="address")
print(p)

# tutorials
# https://www.practicaldatascience.org/html/plotting_part1.html
# https://www.practicaldatascience.org/html/plotting_part2.html

# import pandas as pd
# from plotnine import *

# gapminder = pd.read_csv("gapminder-FiveYearData.csv")

# # to download the data directly:
# # gapminder = pd.read_csv(
# #     "https://raw.githubusercontent.com/swcarpentry/r-novice-gapminder/gh-pages/_episodes_rmd/data/gapminder-FiveYearData.csv")

# print(gapminder.head())

# gapminder_2007 = gapminder[gapminder.year == 2007]
# print(ggplot(gapminder_2007, aes(x='gdpPercap',
#                                  y='lifeExp', color='continent', size='pop')) +
#       geom_point(alpha=0.5) +
#       scale_x_log10() +
#       labs(title="GDP versus life expectancy in 2007",
#            x="GDP per capita (log scale)",
#            y="Life expectancy",
#            size="Popoulation",
#            color="Continent") +
#       facet_wrap('continent'))
