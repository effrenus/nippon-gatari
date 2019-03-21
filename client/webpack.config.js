const path = require('path');
const webpack = require("webpack");
const outputDir = path.join(__dirname, 'build/');

const isProd = process.env.NODE_ENV === 'production';

module.exports = {
  entry: './lib/js/src/Index.bs.js',
  devtool: "source-map",
  mode: isProd ? 'production' : 'development',
  output: {
    path: outputDir,
    filename: 'Index.js'
  },
  plugins: [
    new webpack.DefinePlugin({
      'process.env.GQL_URI': JSON.stringify(isProd ? "/graphql" : "http://localhost:8080/graphql")
    })
  ],
  devServer: {
    compress: true,
    contentBase: outputDir,
    port: process.env.PORT || 8000,
    historyApiFallback: true
  }
};
