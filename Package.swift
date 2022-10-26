// swift-tools-version:5.0

import PackageDescription

let package = Package(
    name: "TPCircularBuffer",
    products: [
        .library(name: "TPCircularBuffer", targets: ["CTPCircularBuffer"]),
    ],
    targets: [
        .target(name: "CTPCircularBuffer", path: "", publicHeadersPath: ""),
    ]
)
