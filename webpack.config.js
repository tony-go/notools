const path = require("path")
const HtmlWebpackPlugin = require("html-webpack-plugin")
const CopyPlugin = require("copy-webpack-plugin")
const outputDir = path.join(__dirname, "build/")

const isProd = process.env.NODE_ENV === "production"

module.exports = {
  entry: "./src/Index.bs.js",
  mode: isProd ? "production" : "development",
  devtool: "source-map",
  output: {
    path: outputDir,
    filename: "Index.js"
  },
  plugins: [
    new CopyPlugin({
      patterns: [
        {
          from: path.resolve(__dirname, 'public/_redirects'),
        },
      ],
    }),
    new HtmlWebpackPlugin({
      template: "public/index.html",
      inject: false
    })
  ],
  devServer: {
    compress: true,
    contentBase: outputDir,
    port: process.env.PORT || 8000,
    historyApiFallback: true
  },
  module: {
    rules: [
      {
        test: /\.css$/,
        use: ["style-loader", "css-loader"]
      }
    ]
  }
}
