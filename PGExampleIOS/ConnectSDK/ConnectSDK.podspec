#
#  Be sure to run `pod spec lint ConnectSDK.podspec' to ensure this is a
#  valid spec and to remove all comments including this before submitting the spec.
#

Pod::Spec.new do |s|

  s.name         = "ConnectSDK"
  s.version      = "1.7.0"
  s.summary      = "Connect SDK allows you to easily add support for the barcode scanner to your App"

  s.description  = <<-DESC
Connect SDK allows you to easily add support for the barcode scanner to your App!
                   DESC

  s.license = { :file => 'LICENSE', :type => 'ProGlove' }

  s.homepage     = "https://proglove.com/"

  s.author             = { "Workaround GmbH" => "service@proglove.de" }

  s.ios.deployment_target = "9.0"

  s.frameworks = 'CoreBluetooth'

  s.source       = { :path => "." }

  s.vendored_frameworks = "ConnectSDK.xcframework"

end
