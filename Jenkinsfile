pipeline {
  agent {
    label "local"
  }

  parameters {
    booleanParam(
      name: "archive",
      description: "Should artifacts be archived?",
      defaultValue: false
    )
  }

  environment {
    BUILD_DIR = "build"
    BUILD_OUTPUT_DIR = "buildOut"
  }

  options {
    skipDefaultCheckout true
    timeout(time: 20, unit: "MINUTES")
    buildDiscarder logRotator(numToKeepStr: "10", artifactNumToKeepStr: "5")
    timestamps()
  }

  stages {
    stage("Preparation") {
      steps {
        script {
          def scmEnv = checkout scm
          currentBuild.displayName = "${env.BUILD_NUMBER} ${scmEnv.GIT_COMMIT.take(8)}"
        }
      }
    }

    stage("Build") {
      steps {
        echo "#INFO: Building project"
        dir("${env.BUILD_DIR}") {
          sh "cmake .. && make -s"
        }
      }
    }

    stage("Unit tests") {
      steps {
        echo "#INFO: Running unit tests"
        dir("${env.BUILD_DIR}") {
          sh "ctest -V --no-compress-output -T test"
        }
      }

      post {
        always {
          xunit(
            tools: [CTest(
              pattern: "${env.BUILD_DIR}/Testing/*/Test.xml",
              failIfNotNew: true,
              stopProcessingIfError: true
            )],
            thresholds: [failed(unstableThreshold: "0", failureThreshold: "0")]
          )
        }
      }
    }

    stage("Archive artifacts") {
      when {
        beforeAgent true
        expression {
          params.archive
        }
      }

      steps {
        archiveArtifacts(artifacts: "${env.BUILD_OUTPUT_DIR}/bin/*.exe", onlyIfSuccessful: true)
      }
    }
  }

  post {
    cleanup {
      cleanWs()
    }
  }
}
