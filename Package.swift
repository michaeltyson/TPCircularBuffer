// swift-tools-version:5.5
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "TPCircularBuffer",
    products: [
        .library(
            name: "TPCircularBuffer",
            targets: ["TPCircularBuffer"]),
    ],
    dependencies: [
    ],
    targets: [
        .target(
            name: "TPCircularBuffer",
            dependencies: []),
    ]
)
