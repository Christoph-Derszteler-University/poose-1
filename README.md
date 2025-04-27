# Development

## Generating the documentation

This project uses [Doxygen](https://www.doxygen.nl/)
to generate documentation from the source code,
the source code is adequately enhanced with Doxygen-styled comments.
To generate the documentation, run the following command
(you need to have Doxygen installed).
The output is generated in the `docs` directory, where you can find a
`html/index.html` file to view the documentation in your browser.

```sh
doxygen Doxyfile
```