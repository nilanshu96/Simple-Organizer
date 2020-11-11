simpleorganizer_sources = [
  'main.c',
  'simpleorganizer-window.c',
]

simpleorganizer_deps = [
  dependency('gio-2.0', version: '>= 2.50'),
  dependency('gtk+-3.0', version: '>= 3.22'),
  dependency('libhandy-1', version: '>= 0.9.90')
]

gnome = import('gnome')

simpleorganizer_sources += gnome.compile_resources('simpleorganizer-resources',
  'simpleorganizer.gresource.xml',
  c_name: 'simpleorganizer'
)

executable('simpleorganizer', simpleorganizer_sources,
  dependencies: simpleorganizer_deps,
  install: true,
)
