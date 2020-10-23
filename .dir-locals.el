((nil . ((cmake-ide-project-dir . "~/Base/Knowledge/learn_cpp/CppProjects/FirstGameEngine")
        (cmake-ide-build-dir . "~/Base/Knowledge/learn_cpp/CppProjects/FirstGameEngine/build-emacs")
        (cmake-ide-cmake-opts . "-DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_TOOLCHAIN_FILE='~/Programs/vcpkg/scripts/buildsystems/vcpkg.cmake' -DPORTABLE=1 -DCMAKE_CXX_COMPILER='/usr/bin/clang++'")
        (projectile-project-name . "FirstGameEngine")
        (projectile-project-run-cmd . "./run.sh")
        (projectile-project-test-cmd . "./test.sh")
        (setq helm-ctest-build-dir "~/Base/Knowledge/learn_cpp/CppProjects/FirstGameEngine/build-emacs")
        (helm-make-build-dir . "build")
        (helm-make-arguments . "-j4"))))

;; ((c++-mode . ((lsp-clients-clangd-args . ("--compile-commands-dir=build-emacs"
                                          ;; "--pch-storage=memory"
                                          ;; "--background-index"
                                          ;; "-j=4")))))

(c++-mode . ((c-basic-offset . 4)
          (tab-width . 4)
          (indent-tabs-mode . t)))

;;((c++-mode . ((dap-debug-template-configurations . (
   ;;                                                  ("my_app"
   ;;                                                  :type "gdb"
   ;;                                                :target "/home/user/src/build/app/my_app"
            ;                                         )
             ;                                       )))))
