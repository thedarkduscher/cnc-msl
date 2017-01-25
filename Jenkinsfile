node {
    stage('scm'){
        checkout scm
    }

    stage ('reference') {
        echo "We are currently working on branch: ${env.BRANCH_NAME}"

        if(env.BRANCH_NAME == 'master') {
            sh 'pip3 install pystache'
            sh 'doxygen'
            sh 'doxygen_renderer docs/xml docs/public'
            sh 'git filter-branch --prune-empty --subdirectory-filter docs/public'
            sh 'git add .'
            sh 'git commit -m "Build reference"'
            sh 'git push gh-pages'
        }
    }
}
