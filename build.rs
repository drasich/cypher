#![feature(append)]

extern crate pkg_config;
extern crate gcc;


use std::env;
use std::path::PathBuf;

fn main() {
    let mut paths  = Vec::new();
    if let Ok(ref mut info) = pkg_config::find_library("eina") {
        //build_elementary_key(&info.include_paths);
        paths.append(&mut info.include_paths);
    }
    if let Ok(ref mut info) = pkg_config::find_library("eet") {
        paths.append(&mut info.include_paths);
    }
    if let Ok(ref mut info) = pkg_config::find_library("evas") {
        paths.append(&mut info.include_paths);
    }
    /*
    if let Ok(ref mut info) = pkg_config::find_library("ecore-x") {
        paths.append(&mut info.include_paths);
    }
    */
    build_cypher(&paths);
}

fn build_cypher(include_paths: &[PathBuf]) {
    let mut config = gcc::Config::new();

    for path in include_paths {
        config.include(path);
    }

    config.file("src/buffer.c")
        .file("src/cypher.c")
        .file("src/fbo.c")
        .file("src/shader.c")
        .file("src/texture.c")
        //.include("src")
        .define("EVAS_GL", None)
        .compile("libcypher.a");
}

