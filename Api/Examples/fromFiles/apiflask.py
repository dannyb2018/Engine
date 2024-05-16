#!/usr/bin/env python

import argparse
from ORE import OREApp
from urllib.parse import unquote
import ORE as ql
import flask
import os
app = flask.Flask(__name__)


@app.route('/file/<path:filename>', methods=['GET', 'POST'])
def get_file(filename):
    filename = unquote(filename)
    fdir, file = os.path.split(filename)

    print("Loading parameters...")
    params = ql.Parameters()
    params.fromFile(filename)

    print("Creating OREApp...")
    os.chdir(fdir + r"\..")
    ore = OREApp(params)

    print("Running ORE process...")
    ore.run()

    print("Run time: %.6f sec" % ore.getRunTime())

    print("ORE process done")

    return {}


if __name__ == '__main__':
    argparser = argparse.ArgumentParser(description='Simple file server')
    argparser.add_argument('--host', type=str, help='The host', default="localhost")
    argparser.add_argument('--port', type=str, help='The server port', default="5000")
    argparser.add_argument('--input_dir', type=str, help='Path containing input files', default='Input')
    argparser.add_argument('--output_dir', type=str, help='Path to write output', default='Output')
    main_args = argparser.parse_args()

    app.run(host=main_args.host, port=main_args.port)
